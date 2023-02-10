#include "pch.h"
#include "PixelHEX.h"

std::string PixelHEX::GetColorsData() const
{
    return *this->format;
}

std::string PixelHEX::GetPixelColorFormat() const
{
    return *this->name;
}

PixelHEX::PixelHEX(std::string format)
{
    if (format.size() != 7 || format[0] != '#') throw std::exception("wrong format");
    this->name = new std::string("hex");
    this->format = new std::string(format);
}

PixelHEX::PixelHEX(const PixelHEX& other)
{
    this->name = new std::string(*other.name);
    this->format = new std::string(*other.format);
}

PixelHEX::PixelHEX(PixelHEX&& other) noexcept
{
    this->name = new std::string(*other.name);
    this->format = new std::string(*other.format);

    other.format = nullptr;
    other.name = nullptr;
}

PixelHEX::~PixelHEX() noexcept
{
    delete this->name;
    delete this->format;
}

PixelHEX& PixelHEX::operator=(const PixelHEX& other)
{
    if (*this != other)
    {
        this->format = other.format;
        this->name = other.name;
    }

    return *this;
}

PixelHEX& PixelHEX::operator=(PixelHEX&& other) noexcept
{
    if (*this != other)
    {
        this->name = other.name;
        this->format = other.format;

        other.format = nullptr;
        other.name = nullptr;
    }

    return *this;
}
