#pragma once

#include "IImage.h"
#include "IImageState.h"

class Image : public IImage
{
public:
    Image(ImageResolution* imageResolution,
        IImageState* imageState);
    Image(const Image& other);
    ~Image() noexcept;
    Image& operator = (const Image& other);
    Image(Image&& other) noexcept;
    Image& operator = (Image&& other);

    std::vector<Pixel*> GetPixelsVector() const;
    std::string GetImageColorFormat() const override;
    ImageResolution* GetImageResolution() const override;

private:
    IImageState* imageStatePixelsVector;
    ImageResolution* imageResolution;

};

bool operator == (const Image& imageFirst, const Image& imageSecond);
bool operator != (const Image& imageFirst, const Image& imageSecond);

std::ostream& operator << (std::ostream& stream, const Image& image);
