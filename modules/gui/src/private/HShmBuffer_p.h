#pragma once

#include "HShmBuffer.h"
#include "HApplication.h"
#include "private/HApplication_p.h"

extern "C" {
#include <wayland-client.h>
}

#include <string>

namespace Ht {

/**
 * @brief Private implementation for HShmBuffer.
 * Allocates a wl_shm pool and wl_buffer backed by shared memory.
 */
struct HShmBuffer::Impl {
    HApplication* app = nullptr;
    wl_shm* shm = nullptr;
    wl_shm_pool* pool = nullptr;
    wl_buffer* buffer = nullptr;
    void* mapped = nullptr;
    int width = 0;
    int height = 0;
    int stride = 0;
    size_t size = 0;
    int fd = -1;
    std::string name;
};

} // namespace Ht

