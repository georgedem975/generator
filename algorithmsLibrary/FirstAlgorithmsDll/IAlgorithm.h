#pragma once

#include "Image.h"

class IAlgorithm
{
public:
    virtual Image DoAlgorithm() = 0;
};