#pragma once

#include "IAlgorithm.h"

class IImageGeneratorService
{
public:
    virtual Image GenerateImage() = 0;
    virtual void SetAlgorithm(IAlgorithm* newAlgorithm) = 0;
};