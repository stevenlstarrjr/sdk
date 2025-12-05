#pragma once

#include "HPicture.h"
#include "include/core/SkPicture.h"
#include "include/core/SkRefCnt.h"

namespace Ht {

struct HPicture::Impl {
    sk_sp<SkPicture> picture;
};

} // namespace Ht

