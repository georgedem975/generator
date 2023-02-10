#include "pch.h"
#include "GenerateImageByDiamondSquare.h"
#include "ImageState.h"


GenerateImageByDiamondSquare::GenerateImageByDiamondSquare(Image* image, GenerateLevelsImageHandler* handler)
{
    this->image = image;
    this->handler = handler;
}

GenerateImageByDiamondSquare::~GenerateImageByDiamondSquare()
{
    this->image = nullptr;
    this->handler = nullptr;
}

struct FourTops
{
    FourTops(int x1, int x2, int x3, int x4, int y1, int y2, int y3, int y4)
    {
        this->x1 = x1;
        this->x2 = x2;
        this->x3 = x3;
        this->x4 = x4;
        this->y3 = y3;
        this->y4 = y4;
        this->y1 = y1;
        this->y2 = y2;
    }

    int x1, x2, x3, x4;
    int y1, y2, y3, y4;
};

std::vector<int> GenerateImageByDiamondSquare::GetRandomHeights()
{
    std::vector<std::vector<int>> result = std::vector<std::vector<int>>();

    int width = this->image->GetImageResolution()->GetImageWidth();

    int height = this->image->GetImageResolution()->GetImageHeight();

    result.reserve(width * height);

    for (int i = 0; i < height; i++)
    {
        result.push_back(std::vector<int>());
        result[i].reserve(width);
        for (int j = 0; j < width; j++)
        {
            result[i].push_back(0);
        }
    }

    result[0][0] = this->GetHeight(-width, width);
    result[0][width - 1] = this->GetHeight(-width, width);
    result[height - 1][0] = this->GetHeight(-width, width);
    result[height - 1][width - 1] = this->GetHeight(-width, width);

    std::queue<FourTops> queue = std::queue<FourTops>();

    queue.push(FourTops(0, width - 1, 0, width - 1, 0, 0, height - 1, height - 1));

    while (!queue.empty())
    {
        int p1x = queue.front().x1;
        int p1y = queue.front().y1;

        int p2x = queue.front().x2;
        int p2y = queue.front().y2;

        int p3x = queue.front().x3;
        int p3y = queue.front().y3;

        int p4x = queue.front().x4;
        int p4y = queue.front().y4;

        if (p1x + 1 == p2x || p3y - 1 == p1y)
        {
            queue.pop();
            continue;
        }

        int middleX = std::abs(p2x - p1x) / 2;
        int middleY = std::abs(p3y - p1y) / 2;

        int length = p2x - p1x;

        result[middleY][middleX] = (result[p1y][p1x] + result[p2y][p2x] + result[p3y][p3x] + result[p4y][p4x]) / 4 +
            this->GetHeight(-length * 2, length * 2);

        int p5x = std::abs(p2x - p1x) / 2, p5y = p1y;
        int p6x = p2x, p6y = std::abs(p3y - p1y) / 2;
        int p7x = std::abs(p2x - p1x) / 2, p7y = p3y;
        int p8x = p1x, p8y = std::abs(p3y - p1y) / 2;


        result[p5y][p5x] = (result[p1y][p1x] + result[p2y][p2x]) / 2 + this->GetHeight(-length, length);
        result[p6y][p6x] = (result[p2y][p2x] + result[p4y][p4x]) / 2 + this->GetHeight(-length, length);
        result[p7y][p7x] = (result[p3y][p3x] + result[p4y][p4x]) / 2 + this->GetHeight(-length, length);
        result[p8y][p8x] = (result[p1y][p1x] + result[p3y][p3x]) / 2 + this->GetHeight(-length, length);

        queue.pop();

        if (std::abs(p5x - p1x) <= 1 && std::abs(p8y - p1y) <= 1 && std::abs(p2x - p5x) <= 1 && std::abs(p3x - p8x) <= 1)
        {
            queue.push(FourTops(p1x, p5x, p8x, middleX, p1y, p5y, p8y, middleY));
            queue.push(FourTops(p5x, p2x, middleX, p6x, p5y, p2y, middleY, p6y));
            queue.push(FourTops(p8x, middleX, p3x, p7x, p8y, middleY, p3y, p7y));
            queue.push(FourTops(middleX, p6x, p7x, p4x, middleY, p6y, p7y, p4y));
        }
    }

    std::vector<int> res = std::vector<int>();

    res.reserve(height * width);

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            res.push_back(result[i][j]);
        }
    }

    return res;
}

int GenerateImageByDiamondSquare::GetHeight(int minimal, int maximal)
{
    std::srand((std::time(NULL)));

    return minimal + std::rand() % (maximal - minimal + 1);
}

Image GenerateImageByDiamondSquare::DoAlgorithm()
{
    std::vector<int> result = this->GetRandomHeights();

    std::vector<Pixel*> pixelsVector = this->image->GetPixelsVector();

    for (int i = 0; i < this->image->GetImageResolution()->GetImageHeight(); i++)
    {
        for (int j = 0; j < this->image->GetImageResolution()->GetImageWidth(); j++)
        {
            pixelsVector[i * this->image->GetImageResolution()->GetImageHeight() + j] =
                new PixelRGB(this->handler->GetPixelByLevel(result[i *
                    this->image->GetImageResolution()->GetImageHeight() + j]));
        }
    }

    return Image(new ImageResolution(this->image->GetImageResolution()->GetImageWidth(),
        this->image->GetImageResolution()->GetImageHeight()),
        new ImageState(pixelsVector));
}

