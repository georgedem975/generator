#pragma once

#include <thread>
#include <queue>
#include "IAlgorithm.h"

class GenerateHorizonImageByDiamondSquareMidpointDisplacement : public IAlgorithm
{
public:
    GenerateHorizonImageByDiamondSquareMidpointDisplacement() = delete;
    GenerateHorizonImageByDiamondSquareMidpointDisplacement(Image* image, int countStars, int epsilon = 2);
    ~GenerateHorizonImageByDiamondSquareMidpointDisplacement();
    GenerateHorizonImageByDiamondSquareMidpointDisplacement(const GenerateHorizonImageByDiamondSquareMidpointDisplacement& other);
    GenerateHorizonImageByDiamondSquareMidpointDisplacement(GenerateHorizonImageByDiamondSquareMidpointDisplacement&& other);
    GenerateHorizonImageByDiamondSquareMidpointDisplacement& operator = (const GenerateHorizonImageByDiamondSquareMidpointDisplacement& other);
    GenerateHorizonImageByDiamondSquareMidpointDisplacement& operator = (GenerateHorizonImageByDiamondSquareMidpointDisplacement&& other);

    Image DoAlgorithm() override;

private:
    void CreationNightScene();
    void CreationStarsOnScene(const Image& image);
    std::vector<std::pair<int, int>> CreationHorizon(int height, int width);
    void CreationHorizonOnScene(std::vector<std::pair<int, int>> pixelsVectorLine);
    std::pair<int, int> GetRandomStarPosition(int height, int width);
    int GetRandomHeightPosition(int minimal, int maximal);

    Image* image;
    int countStarsOnImage;
    int epsilon;
};