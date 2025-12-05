#include "HPictureRecorder.h"

#include "HPicture.h"
#include "HPainter.h"
#include "HRectF.h"
#include "private/HPainterImpl.h"
#include "private/HPictureImpl.h"

#include "include/core/SkPictureRecorder.h"
#include "include/core/SkPicture.h"
#include "include/core/SkRect.h"

namespace Ht {

struct HPictureRecorder::Impl {
    std::unique_ptr<SkPictureRecorder> recorder;
    HPainter painter;
    bool recording = false;
    HRectF bounds;
};

HPictureRecorder::HPictureRecorder()
    : m_impl(std::make_unique<Impl>()) {
}

HPictureRecorder::~HPictureRecorder() = default;

bool HPictureRecorder::begin(const HRectF& bounds) {
    if (m_impl->recording) {
        return false;
    }

    m_impl->recorder = std::make_unique<SkPictureRecorder>();
    SkRect r = SkRect::MakeXYWH(bounds.x(), bounds.y(), bounds.width(), bounds.height());
    SkCanvas* canvas = m_impl->recorder->beginRecording(r);
    if (!canvas) {
        m_impl->recorder.reset();
        return false;
    }

    // Configure painter to record into this canvas
    HPainter::Impl* impl = m_impl->painter.impl();
    impl->canvas = canvas;
    impl->active = true;
    impl->targetImage = nullptr;

    m_impl->bounds = bounds;
    m_impl->recording = true;
    return true;
}

HPainter* HPictureRecorder::painter() {
    if (!m_impl->recording) {
        return nullptr;
    }
    return &m_impl->painter;
}

HPicture HPictureRecorder::end() {
    HPicture picture;
    if (!m_impl->recording || !m_impl->recorder) {
        return picture;
    }

    // Finish recording
    sk_sp<SkPicture> skPicture = m_impl->recorder->finishRecordingAsPicture();
    m_impl->recorder.reset();
    m_impl->recording = false;

    // Deactivate painter
    HPainter::Impl* impl = m_impl->painter.impl();
    impl->canvas = nullptr;
    impl->active = false;
    impl->targetImage = nullptr;

    if (skPicture) {
        picture.impl()->picture = std::move(skPicture);
    }
    return picture;
}

bool HPictureRecorder::isRecording() const {
    return m_impl->recording;
}

} // namespace Ht
