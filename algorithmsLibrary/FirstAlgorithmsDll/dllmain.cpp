// dllmain.cpp : Определяет точку входа для приложения DLL.
#include "pch.h"

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}


#include <vector>
#include "PixelRGB.h"
#include "Image.h"
#include "ImageState.h"
#include "GenerateLevelsImageHandler.h"
#include "GenerateImageByDiamondSquare.h"
#include "GenerateHorizonImageByDiamondSquareMidpointDisplacement.h"
#include "ImageGeneratorService.h"


extern "C"
{
    Image* image;


    __declspec (dllexport) int __stdcall Java_CGenerator_getSize()
    {
        return image->GetPixelsVector().size();
    }

    __declspec (dllexport) int __stdcall Java_CGenerator_getPixelRGB(int index, char mod)
    {
        if (mod == 'r')
            return ((PixelRGB*)((*image).GetPixelsVector()[index]))->getR();

        if (mod == 'g')
            return ((PixelRGB*)((*image).GetPixelsVector()[index]))->getG();

        if (mod == 'b')
            return ((PixelRGB*)((*image).GetPixelsVector()[index]))->getB();
    }

    __declspec (dllexport) void __stdcall Java_CGenerator_generateImageByDSMD()
    {
        auto pixels = std::vector<Pixel*>();

        for (int i = 0; i < 900; i++)
        {
            pixels.push_back(new PixelRGB(255, 255, 255));
        }


        IImageState* state = new ImageState(pixels);
        image = new Image(new ImageResolution(30, 30), state);


        IAlgorithm* algorithm = new GenerateHorizonImageByDiamondSquareMidpointDisplacement(image, 15, 2);

        IImageGeneratorService* imageGeneratorService = new ImageGeneratorService(algorithm);

        Image imageResult = imageGeneratorService->GenerateImage();
    }

    __declspec (dllexport) void __stdcall Java_CGenerator_generateImageByDS()
    {
        auto pixels = std::vector<Pixel*>();

        for (int i = 0; i < 900; i++)
        {
            pixels.push_back(new PixelRGB(255, 255, 255));
        }


        IImageState* state = new ImageState(pixels);
        image = new Image(new ImageResolution(30, 30), state);


        GenerateLevelsImageHandler* handler = new GenerateLevelsImageHandler(-5, new PixelRGB(0, 0, 115), nullptr);

        IAlgorithm* algorithm = new GenerateImageByDiamondSquare(image, handler);

        GeneratorHandler* handlerOne = new GenerateLevelsImageHandler(0, new PixelRGB(128, 128, 0), nullptr);
        GeneratorHandler* handlerTwo = new GenerateLevelsImageHandler(1, new PixelRGB(0, 255, 0), nullptr);
        GeneratorHandler* handlerThree = new GenerateLevelsImageHandler(2, new PixelRGB(0, 128, 0), nullptr);
        GeneratorHandler* handlerFour = new GenerateLevelsImageHandler(6, new PixelRGB(128, 128, 128), nullptr);
        GeneratorHandler* handlerFive = new GenerateLevelsImageHandler(17, new PixelRGB(255, 255, 255), nullptr);

        handler->SetNext(handlerOne);
        handlerOne->SetNext(handlerTwo);
        handlerTwo->SetNext(handlerThree);
        handlerThree->SetNext(handlerFour);
        handlerFour->SetNext(handlerFive);

        IImageGeneratorService* imageGeneratorService = new ImageGeneratorService(algorithm);

        Image imageResult = imageGeneratorService->GenerateImage();
    }
}