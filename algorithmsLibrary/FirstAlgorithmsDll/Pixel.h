#pragma once

#include <iostream>
#include <string>

class Pixel
{
public:
    virtual std::string GetPixelColorFormat() const = 0;
    virtual std::string GetColorsData() const = 0;
};

bool operator == (const Pixel& pixelFirst, const Pixel& pixelSecond);
bool operator != (const Pixel& pixelFirst, const Pixel& pixelSecond);

std::ostream& operator << (std::ostream& stream, const Pixel& pixel);
