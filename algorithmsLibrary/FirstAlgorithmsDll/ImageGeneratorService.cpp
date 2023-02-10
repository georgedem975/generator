#include "pch.h"
#include "ImageGeneratorService.h"

Image ImageGeneratorService::GenerateImage()
{
    return this->generateImageAlgorithm->DoAlgorithm();
}

void ImageGeneratorService::SetAlgorithm(IAlgorithm* newAlgorithm)
{
    if (newAlgorithm == nullptr) throw std::exception("algorithm is not null");

    this->generateImageAlgorithm = newAlgorithm;
}

ImageGeneratorService::ImageGeneratorService(IAlgorithm* algorithm)
{
    if (algorithm == nullptr) throw std::exception("algorithm is not null");

    this->generateImageAlgorithm = algorithm;
}

ImageGeneratorService::ImageGeneratorService(ImageGeneratorService&& other)
{
    this->generateImageAlgorithm = other.generateImageAlgorithm;

    other.generateImageAlgorithm = nullptr;
}

ImageGeneratorService::ImageGeneratorService(const ImageGeneratorService& other)
{
    this->generateImageAlgorithm = other.generateImageAlgorithm;
}

ImageGeneratorService::~ImageGeneratorService()
{
    delete this->generateImageAlgorithm;
}

ImageGeneratorService& ImageGeneratorService::operator=(ImageGeneratorService&& other)
{
    if (this->generateImageAlgorithm != other.generateImageAlgorithm)
    {
        this->generateImageAlgorithm = other.generateImageAlgorithm;

        other.generateImageAlgorithm = nullptr;
    }

    return *this;
}

ImageGeneratorService& ImageGeneratorService::operator=(const ImageGeneratorService& other)
{
    if (this->generateImageAlgorithm != other.generateImageAlgorithm)
    {
        this->generateImageAlgorithm = other.generateImageAlgorithm;
    }

    return *this;
}