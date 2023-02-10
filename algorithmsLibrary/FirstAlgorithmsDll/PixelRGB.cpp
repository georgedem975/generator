#include "pch.h"
#include "PixelRGB.h"

std::string PixelRGB::GetPixelColorFormat() const
{
    return *this->name;
}

std::string PixelRGB::GetColorsData() const
{
    return std::string("(" + std::to_string(this->r) +
        "," + std::to_string(this->g) +
        "," + std::to_string(this->b) + ")");
}

PixelRGB::PixelRGB(const PixelRGB& other)
{
    this->name = new std::string(*other.name);

    this->b = other.b;
    this->g = other.g;
    this->r = other.r;
}

PixelRGB::PixelRGB(PixelRGB&& other) noexcept
{
    this->name = new std::string(*other.name);

    this->b = other.b;
    this->g = other.g;
    this->r = other.r;

    other.name = nullptr;

    other.r = 0;
    other.g = 0;
    other.b = 0;
}

PixelRGB::PixelRGB(short r, short g, short b)
{
    this->name = new std::string("rgb");

    this->b = b;
    this->g = g;
    this->r = r;
}

PixelRGB::~PixelRGB() noexcept
{
    delete this->name;
}

PixelRGB& PixelRGB::operator=(const PixelRGB& other)
{
    if (*this != other)
    {
        this->name = new std::string(*other.name);

        this->r = other.r;
        this->b = other.b;
        this->g = other.g;
    }

    return *this;
}

PixelRGB& PixelRGB::operator=(PixelRGB&& other) noexcept
{
    if (*this != other)
    {
        this->name = new std::string(*other.name);

        this->r = other.r;
        this->b = other.b;
        this->g = other.g;

        other.name = nullptr;

        other.r = 0;
        other.b = 0;
        other.g = 0;
    }

    return *this;
}