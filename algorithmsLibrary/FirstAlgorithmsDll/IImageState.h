#pragma once

#include <vector>
#include "Pixel.h"

class IImageState
{
public:
    virtual std::vector<Pixel*> GetPixelsVector() const = 0;
};