#include "HPicture.h"
#include "private/HPictureImpl.h"

namespace Ht {

HPicture::HPicture()
    : m_impl(std::make_unique<Impl>()) {
}

HPicture::HPicture(const HPicture& other)
    : m_impl(std::make_unique<Impl>(*other.m_impl)) {
}

HPicture::HPicture(HPicture&& other) noexcept = default;

HPicture::~HPicture() = default;

HPicture& HPicture::operator=(const HPicture& other) {
    if (this != &other) {
        m_impl = std::make_unique<Impl>(*other.m_impl);
    }
    return *this;
}

HPicture& HPicture::operator=(HPicture&& other) noexcept = default;

bool HPicture::isNull() const {
    return !m_impl || !m_impl->picture;
}

const void* HPicture::rawHandle() const {
    if (!m_impl) {
        return nullptr;
    }
    return static_cast<const void*>(m_impl->picture.get());
}

} // namespace Ht
