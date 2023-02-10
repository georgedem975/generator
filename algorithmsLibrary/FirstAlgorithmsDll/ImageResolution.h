#pragma once

#include <iostream>
#include <string>

class ImageResolution
{
public:
    ImageResolution() = delete;
    ImageResolution(int imageWidth, int imageHeight);
    ~ImageResolution() noexcept;
    ImageResolution(const ImageResolution& other);
    ImageResolution& operator = (const ImageResolution& other);
    ImageResolution(ImageResolution&& other) noexcept;
    ImageResolution& operator = (ImageResolution&& other) noexcept;

    int GetImageWidth() const;
    int GetImageHeight() const;

    [[nodiscard]] std::pair<int, int> GetImageWidthAndHeight() const;

private:
    int imageWidth;
    int imageHeight;
};

bool operator == (const ImageResolution& imageResolutionFirst, const ImageResolution& imageResolutionSecond);
bool operator != (const ImageResolution& imageResolutionFirst, const ImageResolution& imageResolutionSecond);

std::ostream& operator << (std::ostream& stream, const ImageResolution& imageResolution);
