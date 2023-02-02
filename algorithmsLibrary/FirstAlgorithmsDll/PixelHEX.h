#pragma once

#include "Pixel.h"

class PixelHEX : public Pixel
{
public:
    PixelHEX() = delete;
    PixelHEX(std::string format);
    ~PixelHEX() noexcept;
    PixelHEX(const PixelHEX& other);
    PixelHEX& operator = (const PixelHEX& other);
    PixelHEX(PixelHEX&& other) noexcept;
    PixelHEX& operator = (PixelHEX&& other) noexcept;


    std::string GetPixelColorFormat() const override;
    std::string GetColorsData() const override;

private:
    std::string* name;
    std::string* format;
};