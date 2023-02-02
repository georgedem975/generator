#pragma once

#include "IImageGeneratorService.h"

class ImageGeneratorService : public IImageGeneratorService
{
public:
    ImageGeneratorService() = delete;
    ImageGeneratorService(IAlgorithm* algorithm);
    ~ImageGeneratorService();
    ImageGeneratorService(const ImageGeneratorService& other);
    ImageGeneratorService(ImageGeneratorService&& other);
    ImageGeneratorService& operator = (const ImageGeneratorService& other);
    ImageGeneratorService& operator = (ImageGeneratorService&& other);


    Image GenerateImage() override;
    void SetAlgorithm(IAlgorithm* newAlgorithm) override;

private:
    IAlgorithm* generateImageAlgorithm;
};
