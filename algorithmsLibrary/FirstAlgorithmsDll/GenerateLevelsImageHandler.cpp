#include "pch.h"
#include "GenerateLevelsImageHandler.h"

PixelRGB GenerateLevelsImageHandler::GetPixelByLevel(int level)
{
    if (level < this->level)
        return *this->pixel;
    if (this->nextHandler == nullptr)
        return PixelRGB(255, 255, 255);
    return nextHandler->GetPixelByLevel(level);
}

GenerateLevelsImageHandler::GenerateLevelsImageHandler(int level, PixelRGB* pixel,
    GenerateLevelsImageHandler* nextHandler)
{
    this->level = level;
    this->pixel = pixel;
    this->nextHandler = nextHandler;
}

GenerateLevelsImageHandler::GenerateLevelsImageHandler(GenerateLevelsImageHandler&& other)
{
    this->nextHandler = other.nextHandler;
    this->level = other.level;
    this->pixel = other.pixel;

    other.nextHandler = nullptr;
    other.pixel = nullptr;
    other.level = 0;
}

GenerateLevelsImageHandler::GenerateLevelsImageHandler(const GenerateLevelsImageHandler& other)
{
    this->nextHandler = other.nextHandler;
    this->level = other.level;
    this->pixel = other.pixel;
}

GenerateLevelsImageHandler::~GenerateLevelsImageHandler()
{
    this->nextHandler = nullptr;
    this->pixel = nullptr;
    this->level = 0;
}

void GenerateLevelsImageHandler::SetNext(GeneratorHandler* nextHandler)
{
    this->nextHandler = nextHandler;
}

