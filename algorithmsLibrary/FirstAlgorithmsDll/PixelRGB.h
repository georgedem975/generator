#pragma once

#include "Pixel.h"

class PixelRGB : public Pixel
{
public:
    PixelRGB() = delete;
    PixelRGB(short r, short g, short b);
    ~PixelRGB() noexcept;
    PixelRGB(const PixelRGB& other);
    PixelRGB& operator = (const PixelRGB& other);
    PixelRGB(PixelRGB&& other) noexcept;
    PixelRGB& operator = (PixelRGB&& other) noexcept;

    std::string GetPixelColorFormat() const override;
    std::string GetColorsData() const override;
    short getR() const { return this->r; }
    short getG() const { return this->g; }
    short getB() const { return this->b; }

private:
    std::string* name;

    short r;
    short g;
    short b;
};