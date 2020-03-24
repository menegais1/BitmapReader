#ifndef BITMAP_H
#define BITMAP_H

#include <string>
#include <fstream>
#include <iostream>
#include "../Utilities.h"

class FileHeader
{
public:
    short BfType;
    int BfSize;
    short BfReser1;
    short BfReser2;
    int BfOffSetBits;

    void print()
    {
        std::cout << "BfType:" << BfType << std::endl;
        std::cout << "BfSize:" << BfSize << std::endl;
        std::cout << "BfReser1:" << BfReser1 << std::endl;
        std::cout << "BfReser1:" << BfReser1 << std::endl;
        std::cout << "BfOffSetBits:" << BfOffSetBits << std::endl;
    }
};

class BitmapHeader
{
public:
    int BiSize;
    int BiWidth;
    int BiHeight;
    short BiPlanes;
    short BiBitCount;
    int BiCompress;
    int BiSizeImag;
    int BiXPPMeter;
    int BiYPPMeter;
    int BiClrUsed;
    int BiClrImpor;

    void print()
    {
        std::cout << "BiSize:" << BiSize << std::endl;
        std::cout << "BiWidth:" << BiWidth << std::endl;
        std::cout << "BiHeight:" << BiHeight << std::endl;
        std::cout << "BiPlanes:" << BiPlanes << std::endl;
        std::cout << "BiBitCount:" << BiBitCount << std::endl;
        std::cout << "BiCompress:" << BiCompress << std::endl;
        std::cout << "BiSizeImag:" << BiSizeImag << std::endl;
        std::cout << "BiXPPMeter:" << BiXPPMeter << std::endl;
        std::cout << "BiYPPMeter:" << BiYPPMeter << std::endl;
        std::cout << "BiClrUsed:" << BiClrUsed << std::endl;
        std::cout << "BiClrImpor:" << BiClrImpor << std::endl;
    }
};

class Bitmap
{
public:
    std::string fileName;
    int width;
    int height;
    Bitmap(std::string fileName);
    Color *getPixelColorAtPosition(int l, int c) const;
    Int2 getPixelPositionOnScreen(int l, int c) const;
    void flipImageInX();
    void flipImageInY();
    void rotateImage(float angle);
    void convertImageToGrayScale();
    void scaleImage(float scale);
    int *getHistogramForChannel(Channel c) const;

private:
    FileHeader *fileHeader;
    BitmapHeader *bitmapHeader;
    Color **colorPallete;
    Color **bitmapArray;
    bool colorPalleteExists;
    float imageRotation;
    void openFile(std::string filename, std::fstream &file);
    void closeFile(std::fstream &file);
    void loadFileHeader(std::fstream &file);
    void loadBitmapHeader(std::fstream &file);
    bool checkColorPallete(std::fstream &file);
    void loadColorPallete(std::fstream &file);
    void loadImage(std::fstream &file);
    Color *getPixelFromPallete(u_char pixelValue);
    Bitmap(int width, int height);
};

#endif
