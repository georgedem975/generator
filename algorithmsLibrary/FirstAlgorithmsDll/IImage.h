#pragma once

#include "ImageResolution.h"

class IImage
{
public:
    virtual ImageResolution* GetImageResolution() const = 0;
    virtual std::string GetImageColorFormat() const = 0;
};