#pragma once

#include <memory>

namespace Ht {

class HWaylandSeat {
public:
    /**
     * @brief Create an input seat for a compositor.
     *
     * Qt Equivalent: QWaylandSeat(QWaylandCompositor *compositor, const QString &name)
     */
    HWaylandSeat(class HWaylandCompositor* compositor, const char* name);
    ~HWaylandSeat();

    HWaylandSeat(const HWaylandSeat&) = delete;
    HWaylandSeat& operator=(const HWaylandSeat&) = delete;
    HWaylandSeat(HWaylandSeat&&) noexcept;
    HWaylandSeat& operator=(HWaylandSeat&&) noexcept;

    const char* name() const;
    bool hasPointer() const;
    bool hasKeyboard() const;
    bool hasTouch() const;

    struct Impl;
    Impl* impl() const { return m_impl.get(); }

private:
    std::unique_ptr<Impl> m_impl;
};

} // namespace Ht
