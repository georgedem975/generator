#include "pch.h"
#include "Pixel.h"

bool operator == (const Pixel& pixelFirst, const Pixel& pixelSecond)
{
    return pixelFirst.GetPixelColorFormat() == pixelSecond.GetPixelColorFormat() &&
        pixelFirst.GetColorsData() == pixelSecond.GetColorsData();
}

bool operator != (const Pixel& pixelFirst, const Pixel& pixelSecond)
{
    return !(pixelFirst == pixelSecond);
}

std::ostream& operator << (std::ostream& stream, const Pixel& pixel)
{
    stream << pixel.GetPixelColorFormat() << pixel.GetColorsData();

    return stream;
}