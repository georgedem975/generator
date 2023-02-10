#pragma once

#include <queue>
#include "IAlgorithm.h"
#include "GenerateLevelsImageHandler.h"

class GenerateImageByDiamondSquare : public IAlgorithm
{
public:
    GenerateImageByDiamondSquare() = delete;
    GenerateImageByDiamondSquare(Image* image, GenerateLevelsImageHandler* handler);
    ~GenerateImageByDiamondSquare();

    Image DoAlgorithm() override;

private:
    int GetHeight(int minimal, int maximal);
    std::vector<int> GetRandomHeights();

    Image* image;
    GenerateLevelsImageHandler* handler;
};