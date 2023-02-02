#pragma once

#include "IImageState.h"

class ImageState : public IImageState
{
public:
    ImageState() = delete;
    ImageState(std::vector<Pixel*> pixels);
    ~ImageState() noexcept;
    ImageState(const ImageState& other);
    ImageState& operator = (const ImageState& other);
    ImageState(ImageState&& other) noexcept;
    ImageState& operator = (ImageState&& other) noexcept;


    std::vector<Pixel*> GetPixelsVector() const override;

private:
    std::vector<Pixel*>* pixelsVector;
};


bool operator == (const ImageState& imageStateFirst, const ImageState& imageStateSecond);
bool operator != (const ImageState& imageStateFirst, const ImageState& imageStateSecond);

std::ostream& operator << (std::ostream& stream, const ImageState& imageState);
