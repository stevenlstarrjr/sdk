#pragma once

#include <memory>

#include "HRectF.h"

namespace Ht {

class HPainter;
class HPicture;

/**
 * @brief HPictureRecorder records drawing commands into an HPicture.
 * Qt Equivalent: QPicture (via QPainter)
 * Skia Backend: SkPictureRecorder
 */
class HPictureRecorder {
public:
    HPictureRecorder();
    ~HPictureRecorder();

    // Non-copyable
    HPictureRecorder(const HPictureRecorder&) = delete;
    HPictureRecorder& operator=(const HPictureRecorder&) = delete;

    // Begin recording into an internal picture with given logical bounds.
    bool begin(const HRectF& bounds);

    // Access the HPainter used for recording.
    HPainter* painter();

    // Finish recording and return the resulting picture.
    HPicture end();

    bool isRecording() const;

private:
    struct Impl;
    std::unique_ptr<Impl> m_impl;
};

} // namespace Ht

