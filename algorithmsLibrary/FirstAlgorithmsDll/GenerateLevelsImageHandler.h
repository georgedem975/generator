#pragma once

#include "GeneratorHandler.h"

class GenerateLevelsImageHandler : public GeneratorHandler
{
public:
    GenerateLevelsImageHandler() = delete;
    GenerateLevelsImageHandler(int level, PixelRGB* pixel, GenerateLevelsImageHandler* nextHandler);
    ~GenerateLevelsImageHandler();
    GenerateLevelsImageHandler(const GenerateLevelsImageHandler& other);
    GenerateLevelsImageHandler(GenerateLevelsImageHandler&& other);
    GenerateLevelsImageHandler& operator = (const GenerateLevelsImageHandler& other) = delete;
    GenerateLevelsImageHandler& operator = (GenerateLevelsImageHandler&& other) = delete;

    PixelRGB GetPixelByLevel(int level) override;
    void SetNext(GeneratorHandler* nextHandler) override;


private:
    PixelRGB* pixel;
    GeneratorHandler* nextHandler;
    int level;
};