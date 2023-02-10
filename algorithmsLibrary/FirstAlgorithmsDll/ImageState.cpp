#include "pch.h"
#include "ImageState.h"
#include "PixelHEX.h"

std::vector<Pixel*> ImageState::GetPixelsVector() const
{
    return *this->pixelsVector;
}

ImageState& ImageState::operator=(const ImageState& other)
{
    if (*this != other)
    {
        this->pixelsVector = new std::vector<Pixel*>();

        this->pixelsVector->reserve(other.pixelsVector->size());

        int size = other.pixelsVector->size();

        for (int i = 0; i < size; i++)
        {
            this->pixelsVector->push_back(new PixelHEX(((*other.pixelsVector)[i])->GetColorsData()));
        }
    }

    return *this;
}

ImageState& ImageState::operator=(ImageState&& other) noexcept
{
    if (*this != other)
    {
        this->pixelsVector = new std::vector<Pixel*>();

        this->pixelsVector->reserve(other.pixelsVector->size());

        int size = other.pixelsVector->size();

        for (int i = 0; i < size; i++)
        {
            this->pixelsVector->push_back(new PixelHEX(((*other.pixelsVector)[i])->GetColorsData()));
        }

        other.pixelsVector = nullptr;
    }

    return *this;
}

ImageState::ImageState(std::vector<Pixel*> pixels)
{
    this->pixelsVector = new std::vector<Pixel*>();

    this->pixelsVector->reserve(pixels.size());

    for (int i = 0; i < pixels.size(); i++)
    {
        this->pixelsVector->push_back((pixels[i]));
    }
}

ImageState::ImageState(const ImageState& other)
{
    this->pixelsVector = new std::vector<Pixel*>();

    this->pixelsVector->reserve(other.pixelsVector->size());

    for (int i = 0; i < other.pixelsVector->size(); i++)
    {
        this->pixelsVector->push_back(new PixelHEX((*other.pixelsVector)[i]->GetColorsData()));
    }
}

ImageState::ImageState(ImageState&& other) noexcept
{
    this->pixelsVector = new std::vector<Pixel*>();

    this->pixelsVector->reserve(other.pixelsVector->size());

    for (int i = 0; i < other.pixelsVector->size(); i++)
    {
        this->pixelsVector->push_back(new PixelHEX((*other.pixelsVector)[i]->GetColorsData()));
    }

    other.pixelsVector = nullptr;
}

ImageState::~ImageState() noexcept
{
    delete this->pixelsVector;
}

bool operator == (const ImageState& imageStateFirst, const ImageState& imageStateSecond)
{
    if (imageStateFirst.GetPixelsVector().size() != imageStateSecond.GetPixelsVector().size()) return false;

    int size = imageStateFirst.GetPixelsVector().size();

    for (int i = 0; i < size; i++)
    {
        if (imageStateFirst.GetPixelsVector()[i] != imageStateSecond.GetPixelsVector()[i]) return false;
    }

    return true;
}

bool operator != (const ImageState& imageStateFirst, const ImageState& imageStateSecond)
{
    return !(imageStateSecond == imageStateFirst);
}

std::ostream& operator << (std::ostream& stream, const ImageState& imageState)
{
    int size = imageState.GetPixelsVector().size();

    for (int i = 0; i < size; i++)
    {
        stream << imageState.GetPixelsVector()[i]->GetColorsData() << " ";
    }

    return stream;
}
