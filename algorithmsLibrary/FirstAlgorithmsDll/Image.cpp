#include "pch.h"
#include "Image.h"


ImageResolution* Image::GetImageResolution() const
{
    return this->imageResolution;
}

std::vector<Pixel*> Image::GetPixelsVector() const
{
    return this->imageStatePixelsVector->GetPixelsVector();
}

std::string Image::GetImageColorFormat() const {
    return this->imageStatePixelsVector->GetPixelsVector()[0]->GetPixelColorFormat();
}

Image::Image(const Image& other)
{
    this->imageResolution = other.imageResolution;

    this->imageStatePixelsVector = other.imageStatePixelsVector;
}

Image::Image(Image&& other) noexcept
{
    this->imageResolution = other.imageResolution;

    this->imageStatePixelsVector = other.imageStatePixelsVector;

    other.imageResolution = nullptr;
    other.imageStatePixelsVector = nullptr;
}

Image::Image(ImageResolution* imageResolution,
    IImageState* imageStatePixelsVector)
{
    this->imageResolution = imageResolution;

    this->imageStatePixelsVector = imageStatePixelsVector;

    int vectorSize = this->imageStatePixelsVector->GetPixelsVector().size();

    if (vectorSize != this->imageResolution->GetImageWidth() * this->imageResolution->GetImageHeight()) throw std::exception("wrong size of image");
}

Image::~Image() noexcept
{
    delete this->imageStatePixelsVector;
    delete this->imageResolution;
}

Image& Image::operator=(const Image& other)
{
    if (*this != other)
    {
        this->imageResolution = other.imageResolution;

        this->imageStatePixelsVector = other.imageStatePixelsVector;
    }

    return *this;
}

Image& Image::operator=(Image&& other)
{
    if (*this != other)
    {
        this->imageResolution = other.imageResolution;

        this->imageStatePixelsVector = other.imageStatePixelsVector;

        other.imageStatePixelsVector = nullptr;
        other.imageResolution = nullptr;
    }

    return *this;
}


bool operator == (const Image& imageFirst, const Image& imageSecond)
{
    if (imageFirst.GetImageColorFormat() != imageSecond.GetImageColorFormat())

        if (imageFirst.GetImageResolution() != imageSecond.GetImageResolution()) return false;

    int sizeOfPixelsVector = imageFirst.GetPixelsVector().size();

    for (int i = 0; i < sizeOfPixelsVector; i++)
    {
        if (imageFirst.GetPixelsVector()[i] != imageSecond.GetPixelsVector()[i]) return false;
    }

    return true;
}

bool operator != (const Image& imageFirst, const Image& imageSecond)
{
    return !(imageFirst == imageSecond);
}

std::ostream& operator << (std::ostream& stream, const Image& image)
{
    stream << "Image\nColor format: " << image.GetImageColorFormat() << "\nImage Resolution: " << *image.GetImageResolution();

    return stream;
}

