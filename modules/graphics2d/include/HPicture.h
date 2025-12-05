#pragma once

#include <memory>

namespace Ht {

/**
 * @brief HPicture records a sequence of drawing commands.
 * Qt Equivalent: QPicture
 * Skia Backend: SkPicture
 */
class HPicture {
public:
    HPicture();
    HPicture(const HPicture& other);
    HPicture(HPicture&& other) noexcept;
    ~HPicture();

    HPicture& operator=(const HPicture& other);
    HPicture& operator=(HPicture&& other) noexcept;

    bool isNull() const;

    // Internal Skia access
    struct Impl;
    Impl* impl() const { return m_impl.get(); }
    const void* rawHandle() const;

private:
    std::unique_ptr<Impl> m_impl;
};

} // namespace Ht

