#pragma once

#include "PixelRGB.h"

class GeneratorHandler
{
public:
    virtual PixelRGB GetPixelByLevel(int level) = 0;
    virtual void SetNext(GeneratorHandler* nextHandler) = 0;
};