#pragma once

#include "HItem.h"
#include "HImage.h"
#include <string>

namespace Ht {

class HImageItem : public HItem {
public:
    HImageItem(HItem* parent = nullptr);
    HImageItem(const HImage& image, HItem* parent = nullptr);
    HImageItem(const std::string& path, HItem* parent = nullptr);
    virtual ~HImageItem();

    void setImage(const HImage& image);
    const HImage& image() const;

    void load(const std::string& path);

    // Override paintContent to draw image
    void paintContent(HPainter& painter) override;

private:
    struct Impl;
    std::unique_ptr<Impl> m_imageImpl;
};

} // namespace Ht
