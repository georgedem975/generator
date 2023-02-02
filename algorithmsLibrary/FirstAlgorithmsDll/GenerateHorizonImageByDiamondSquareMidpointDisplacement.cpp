#include "pch.h"
#include "GenerateHorizonImageByDiamondSquareMidpointDisplacement.h"
#include "ImageState.h"
#include "PixelRGB.h"

Image GenerateHorizonImageByDiamondSquareMidpointDisplacement::DoAlgorithm()
{
    this->CreationNightScene();

    std::thread threadFirst(&GenerateHorizonImageByDiamondSquareMidpointDisplacement::CreationStarsOnScene,
        std::ref(*this), std::ref(*this->image));

    std::vector<std::pair<int, int>> horizonLine = this->CreationHorizon(this->image->GetImageResolution()->GetImageHeight(),
        this->image->GetImageResolution()->GetImageWidth());

    threadFirst.join();

    this->CreationHorizonOnScene(horizonLine);

    return *this->image;
}

void GenerateHorizonImageByDiamondSquareMidpointDisplacement::CreationNightScene()
{
    int height = this->image->GetImageResolution()->GetImageHeight();
    int width = this->image->GetImageResolution()->GetImageWidth();

    if (height < 256)
    {
        int sizeOfImage = this->image->GetImageResolution()->GetImageWidth() * this->image->GetImageResolution()->GetImageHeight();

        std::vector<Pixel*> pixelsVector = std::vector<Pixel*>();

        Pixel* pixel = new PixelRGB(25, 25, 112);

        for (int i = 0; i < sizeOfImage; i++)
        {
            pixelsVector.push_back(pixel);
        }

        ImageResolution* imageResolution = new ImageResolution(this->image->GetImageResolution()->GetImageWidth(),
            this->image->GetImageResolution()->GetImageHeight());

        ImageState* imageState = new ImageState(pixelsVector);

        this->image = new Image(imageResolution, imageState);
    }
    else
    {
        int countLines = height / 200;

        std::vector<Pixel*> pixelsVector = std::vector<Pixel*>();

        for (int line = 0, counter = 0, palette = 0; line < height; line++, counter++)
        {
            Pixel* pixelForVector = new PixelRGB(0, 0, 50 + palette);

            for (int pixel = 0; pixel < width; pixel++)
            {
                pixelsVector.push_back(pixelForVector);

                if (counter == countLines)
                {
                    counter = 0;
                    palette++;
                }
            }
        }

        ImageResolution* imageResolution = new ImageResolution(this->image->GetImageResolution()->GetImageWidth(),
            this->image->GetImageResolution()->GetImageHeight());

        ImageState* imageState = new ImageState(pixelsVector);

        this->image = new Image(imageResolution, imageState);
    }
}

std::pair<int, int>
GenerateHorizonImageByDiamondSquareMidpointDisplacement::GetRandomStarPosition(int height, int width)
{
    std::srand(std::time(NULL));

    int coordinateX = std::rand() % (width + 1);

    int coordinateY = std::rand() % (height + 1);

    return std::pair<int, int>(coordinateX, coordinateY);
}

int GenerateHorizonImageByDiamondSquareMidpointDisplacement::GetRandomHeightPosition(int minimal, int maximal)
{
    std::srand((std::time(NULL)));

    return minimal + std::rand() % (maximal - minimal + 1);
}

void GenerateHorizonImageByDiamondSquareMidpointDisplacement::CreationStarsOnScene(const Image& image)
{
    std::vector<Pixel*> pixelsVector = image.GetPixelsVector();

    for (int counter = 0; counter < this->countStarsOnImage; counter++)
    {
        std::pair<int, int> pointInImage = this->GetRandomStarPosition(image.GetImageResolution()->GetImageHeight(),
            image.GetImageResolution()->GetImageWidth());

        Pixel* pixel = new PixelRGB(255, 255, 255);

        int position = pointInImage.first * pointInImage.second - 2;

        if (position < 0) position = 0;

        pixelsVector[position] = pixel;

        pixelsVector[position + 1] = pixel;
        pixelsVector[std::abs(position - 1)] = pixel;
        pixelsVector[std::abs(position - image.GetImageResolution()->GetImageWidth())] = pixel;

        if (position + image.GetImageResolution()->GetImageWidth() < image.GetImageResolution()->GetImageWidth() * image.GetImageResolution()->GetImageHeight())
        {
            pixelsVector[position + image.GetImageResolution()->GetImageWidth()] = pixel;
        }

    }

    this->image = new Image(new ImageResolution(this->image->GetImageResolution()->GetImageWidth(),
        this->image->GetImageResolution()->GetImageHeight()),
        new ImageState(pixelsVector));
}

std::vector<std::pair<int, int>>
GenerateHorizonImageByDiamondSquareMidpointDisplacement::CreationHorizon(int height, int width)
{
    std::vector<std::pair<int, int>> line = std::vector<std::pair<int, int>>();

    line.reserve(width);

    for (int i = 0; i < width; i++)
    {
        line.push_back(std::pair<int, int>(0, i));
    }

    line[0].first = this->GetRandomHeightPosition(-width, width);
    line[width - 1].first = this->GetRandomHeightPosition(-width, width);

    std::queue<std::pair<int, int>> queue = std::queue<std::pair<int, int>>();

    queue.push(std::pair<int, int>(0, width - 1));

    while (!queue.empty())
    {
        int left = queue.front().first;
        int right = queue.front().second;

        if (left + 1 == right)
        {
            queue.pop();
            continue;
        }

        int middle = (left + right) / 2;

        int length = line[right].second - line[left].second;

        //if (length > height) length = height - 1;

        line[middle].first = (line[left].first + line[right].first) / 2 +
            this->GetRandomHeightPosition(-this->epsilon * length, this->epsilon * length);

        queue.pop();
        queue.push(std::pair<int, int>(left, middle));
        queue.push(std::pair<int, int>(middle, right));
    }

    return line;
}

void GenerateHorizonImageByDiamondSquareMidpointDisplacement::CreationHorizonOnScene(std::vector<std::pair<int, int>> pixelsVectorLine)
{
    std::vector<Pixel*> pixelsVector = this->image->GetPixelsVector();

    Pixel* blackLandPixel = new PixelRGB(0, 0, 0);

    for (int line = 0; line < this->image->GetImageResolution()->GetImageHeight(); line++)
    {
        for (int pixelNumberInLine = 0; pixelNumberInLine < this->image->GetImageResolution()->GetImageWidth(); pixelNumberInLine++)
        {
            if (pixelsVectorLine[pixelNumberInLine].first >= this->image->GetImageResolution()->GetImageHeight() - line)
            {
                pixelsVector[line * this->image->GetImageResolution()->GetImageWidth() + pixelNumberInLine] = blackLandPixel;
            }
        }
    }

    this->image = new Image(new ImageResolution(this->image->GetImageResolution()->GetImageWidth(),
        this->image->GetImageResolution()->GetImageHeight()),
        new ImageState(pixelsVector));
}

GenerateHorizonImageByDiamondSquareMidpointDisplacement&
GenerateHorizonImageByDiamondSquareMidpointDisplacement::operator=(
    GenerateHorizonImageByDiamondSquareMidpointDisplacement&& other)
{
    if (this->image != other.image)
    {
        this->image = other.image;
        this->countStarsOnImage = other.countStarsOnImage;
        this->epsilon = other.epsilon;

        other.image = nullptr;
        other.countStarsOnImage = 0;
        other.epsilon = 0;
    }

    return *this;
}

GenerateHorizonImageByDiamondSquareMidpointDisplacement&
GenerateHorizonImageByDiamondSquareMidpointDisplacement::operator=(
    const GenerateHorizonImageByDiamondSquareMidpointDisplacement& other)
{
    if (this->image != other.image)
    {
        this->image = other.image;
        this->countStarsOnImage = other.countStarsOnImage;
        this->epsilon = other.epsilon;
    }

    return *this;
}

GenerateHorizonImageByDiamondSquareMidpointDisplacement::GenerateHorizonImageByDiamondSquareMidpointDisplacement(
    Image* image, int countStars, int epsilon)
{
    this->image = image;
    this->countStarsOnImage = countStars;
    this->epsilon = epsilon;
}

GenerateHorizonImageByDiamondSquareMidpointDisplacement::GenerateHorizonImageByDiamondSquareMidpointDisplacement(
    GenerateHorizonImageByDiamondSquareMidpointDisplacement&& other)
{
    this->image = other.image;
    this->countStarsOnImage = other.countStarsOnImage;
    this->epsilon = other.epsilon;

    other.image = nullptr;
    other.countStarsOnImage = 0;
    other.epsilon = 0;
}

GenerateHorizonImageByDiamondSquareMidpointDisplacement::GenerateHorizonImageByDiamondSquareMidpointDisplacement(
    const GenerateHorizonImageByDiamondSquareMidpointDisplacement& other)
{
    this->image = other.image;
    this->countStarsOnImage = other.countStarsOnImage;
    this->epsilon = other.epsilon;
}

GenerateHorizonImageByDiamondSquareMidpointDisplacement::~GenerateHorizonImageByDiamondSquareMidpointDisplacement()
{
    delete this->image;
    this->countStarsOnImage = 0;
    this->epsilon = 0;
}
