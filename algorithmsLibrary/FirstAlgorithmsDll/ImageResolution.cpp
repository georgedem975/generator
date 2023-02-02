#include "pch.h"
#include "ImageResolution.h"

int ImageResolution::GetImageHeight() const
{
    return this->imageHeight;
}

int ImageResolution::GetImageWidth() const
{
    return this->imageWidth;
}

std::pair<int, int> ImageResolution::GetImageWidthAndHeight() const
{
    return std::pair<int, int>(this->imageWidth, this->imageHeight);
}

ImageResolution::ImageResolution(const ImageResolution& other)
{
    this->imageWidth = other.imageWidth;
    this->imageHeight = other.imageHeight;
}

ImageResolution::ImageResolution(int imageWidth, int imageHeight) : imageWidth(imageWidth), imageHeight(imageHeight) { }

ImageResolution::ImageResolution(ImageResolution&& other) noexcept
{
    this->imageHeight = other.imageHeight;
    this->imageWidth = other.imageWidth;
}

ImageResolution::~ImageResolution() noexcept = default;

ImageResolution& ImageResolution::operator=(const ImageResolution& other)
{
    if (this != &other)
    {
        this->imageWidth = other.imageWidth;
        this->imageHeight = other.imageHeight;
    }

    return *this;
}

ImageResolution& ImageResolution::operator=(ImageResolution&& other) noexcept
{
    if (this != &other)
    {
        this->imageHeight = other.imageHeight;
        this->imageWidth = other.imageWidth;
    }

    return *this;
}

bool operator == (const ImageResolution& imageResolutionFirst, const ImageResolution& imageResolutionSecond)
{
    return imageResolutionFirst.GetImageWidth() == imageResolutionSecond.GetImageWidth() &&
        imageResolutionFirst.GetImageHeight() == imageResolutionSecond.GetImageHeight();
}

bool operator != (const ImageResolution& imageResolutionFirst, const ImageResolution& imageResolutionSecond)
{
    return !(imageResolutionFirst == imageResolutionSecond);
}

std::ostream& operator << (std::ostream& stream, const ImageResolution& imageResolution)
{
    stream << "image size: (" << std::to_string(imageResolution.GetImageHeight()) <<
        'x' << std::to_string(imageResolution.GetImageWidth()) << ')';
    return stream;
}