#include "HShmBuffer.h"
#include "private/HShmBuffer_p.h"

#include <stdexcept>

extern "C" {
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
}

namespace Ht {

namespace {

static std::string makeShmName() {
    // Simple unique-ish name using PID and an address
    char buf[64];
    std::snprintf(buf, sizeof(buf), "/hultrix-shm-%d-%p", getpid(), buf);
    return std::string(buf);
}

} // namespace

HShmBuffer::HShmBuffer(HApplication* app, int width, int height)
    : m_impl(std::make_unique<Impl>()) {
    m_impl->app = app;
    if (!app || !app->impl() || !app->impl()->shm) {
        throw std::runtime_error("HShmBuffer requires HApplication with wl_shm");
    }

    m_impl->shm = app->impl()->shm;
    m_impl->width = width;
    m_impl->height = height;
    m_impl->stride = width * 4; // WL_SHM_FORMAT_ARGB8888
    m_impl->size = static_cast<size_t>(m_impl->stride) * static_cast<size_t>(height);

    m_impl->name = makeShmName();
    m_impl->fd = shm_open(m_impl->name.c_str(), O_CREAT | O_EXCL | O_RDWR, 0600);
    if (m_impl->fd < 0) {
        throw std::runtime_error("Failed to create shared memory for HShmBuffer");
    }

    // Unlink immediately so it disappears after close
    shm_unlink(m_impl->name.c_str());

    if (ftruncate(m_impl->fd, static_cast<off_t>(m_impl->size)) < 0) {
        close(m_impl->fd);
        m_impl->fd = -1;
        throw std::runtime_error("Failed to resize shared memory for HShmBuffer");
    }

    m_impl->mapped = mmap(nullptr, m_impl->size, PROT_READ | PROT_WRITE, MAP_SHARED, m_impl->fd, 0);
    if (m_impl->mapped == MAP_FAILED) {
        m_impl->mapped = nullptr;
        close(m_impl->fd);
        m_impl->fd = -1;
        throw std::runtime_error("Failed to mmap shared memory for HShmBuffer");
    }

    m_impl->pool = wl_shm_create_pool(m_impl->shm, m_impl->fd, static_cast<int32_t>(m_impl->size));
    if (!m_impl->pool) {
        munmap(m_impl->mapped, m_impl->size);
        m_impl->mapped = nullptr;
        close(m_impl->fd);
        m_impl->fd = -1;
        throw std::runtime_error("Failed to create wl_shm_pool");
    }

    m_impl->buffer = wl_shm_pool_create_buffer(
        m_impl->pool,
        0,
        width,
        height,
        m_impl->stride,
        WL_SHM_FORMAT_ARGB8888);

    if (!m_impl->buffer) {
        wl_shm_pool_destroy(m_impl->pool);
        m_impl->pool = nullptr;
        munmap(m_impl->mapped, m_impl->size);
        m_impl->mapped = nullptr;
        close(m_impl->fd);
        m_impl->fd = -1;
        throw std::runtime_error("Failed to create wl_buffer from wl_shm_pool");
    }
}

HShmBuffer::~HShmBuffer() {
    if (m_impl) {
        if (m_impl->buffer) {
            wl_buffer_destroy(m_impl->buffer);
            m_impl->buffer = nullptr;
        }
        if (m_impl->pool) {
            wl_shm_pool_destroy(m_impl->pool);
            m_impl->pool = nullptr;
        }
        if (m_impl->mapped) {
            munmap(m_impl->mapped, m_impl->size);
            m_impl->mapped = nullptr;
        }
        if (m_impl->fd >= 0) {
            close(m_impl->fd);
            m_impl->fd = -1;
        }
    }
}

HShmBuffer::HShmBuffer(HShmBuffer&&) noexcept = default;
HShmBuffer& HShmBuffer::operator=(HShmBuffer&&) noexcept = default;

int HShmBuffer::width() const {
    return m_impl->width;
}

int HShmBuffer::height() const {
    return m_impl->height;
}

int HShmBuffer::stride() const {
    return m_impl->stride;
}

void* HShmBuffer::data() {
    return m_impl->mapped;
}

const void* HShmBuffer::data() const {
    return m_impl->mapped;
}

void* HShmBuffer::wlBuffer() const {
    return static_cast<void*>(m_impl->buffer);
}

} // namespace Ht

