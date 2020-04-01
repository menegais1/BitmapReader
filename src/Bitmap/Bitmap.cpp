#include "Bitmap.h"
#include <string>
#include <fstream>
#include <iostream>
#include <cmath>
#include <cstring>
#include "../Utilities.h"
using namespace std;

Bitmap::Bitmap(const string fileName)
{
    this->fileName = fileName;
    this->imageRotation = 0;
    fstream file;
    openFile(fileName, file);
    if (!file.is_open())
        return;
    loadFileHeader(file);
    loadBitmapHeader(file);
    colorPalleteExists = checkColorPallete(file);
    if (colorPalleteExists)
    {
        loadColorPallete(file);
    }
    loadImage(file);
    closeFile(file);
    width = bitmapHeader.BiWidth;
    height = bitmapHeader.BiHeight;

    fileHeader.print();
    bitmapHeader.print();
}

void Bitmap::openFile(const string filename, fstream &file)
{
    file.open(filename, fstream::in | fstream::binary);
}

void Bitmap::closeFile(fstream &file)
{
    file.close();
}

void Bitmap::loadFileHeader(fstream &file)
{
    file.read(reinterpret_cast<char *>(&fileHeader.BfType), 2);
    file.read(reinterpret_cast<char *>(&fileHeader.BfSize), 4);
    file.read(reinterpret_cast<char *>(&fileHeader.BfReser1), 2);
    file.read(reinterpret_cast<char *>(&fileHeader.BfReser2), 2);
    file.read(reinterpret_cast<char *>(&fileHeader.BfOffSetBits), 4);
}

void Bitmap::loadBitmapHeader(fstream &file)
{
    file.read(reinterpret_cast<char *>(&bitmapHeader.BiSize), 4);
    file.read(reinterpret_cast<char *>(&bitmapHeader.BiWidth), 4);
    file.read(reinterpret_cast<char *>(&bitmapHeader.BiHeight), 4);
    file.read(reinterpret_cast<char *>(&bitmapHeader.BiPlanes), 2);
    file.read(reinterpret_cast<char *>(&bitmapHeader.BiBitCount), 2);
    file.read(reinterpret_cast<char *>(&bitmapHeader.BiCompress), 4);
    file.read(reinterpret_cast<char *>(&bitmapHeader.BiSizeImag), 4);
    file.read(reinterpret_cast<char *>(&bitmapHeader.BiXPPMeter), 4);
    file.read(reinterpret_cast<char *>(&bitmapHeader.BiYPPMeter), 4);
    file.read(reinterpret_cast<char *>(&bitmapHeader.BiClrUsed), 4);
    file.read(reinterpret_cast<char *>(&bitmapHeader.BiClrImpor), 4);
}

bool Bitmap::checkColorPallete(fstream &file)
{
    if (bitmapHeader.BiBitCount < 24)
        return true;
    return false;
}

void Bitmap::loadColorPallete(fstream &file)
{
    int palleteCount = pow(2, bitmapHeader.BiBitCount);
    colorPallete = new Color[palleteCount];

    for (int i = 0; i < palleteCount; i++)
    {
        file.read(reinterpret_cast<char *>(&colorPallete[i].value[2]), 1);
        file.read(reinterpret_cast<char *>(&colorPallete[i].value[1]), 1);
        file.read(reinterpret_cast<char *>(&colorPallete[i].value[0]), 1);
        file.read(reinterpret_cast<char *>(&colorPallete[i].value[3]), 1);
    }
}

Color Bitmap::getPixelFromPallete(const u_char pixelValue)
{
    Color p;
    p.value[0] = colorPallete[pixelValue].value[0];
    p.value[1] = colorPallete[pixelValue].value[1];
    p.value[2] = colorPallete[pixelValue].value[2];
    p.value[3] = colorPallete[pixelValue].value[3];
    return p;
}

void Bitmap::loadImage(fstream &file)
{
    file.clear();
    file.seekg(fileHeader.BfOffSetBits, ios::beg);
    int rowSize = ceil((bitmapHeader.BiBitCount * bitmapHeader.BiWidth) / 32) * 4;
    int padding = rowSize - (bitmapHeader.BiBitCount / 8 * bitmapHeader.BiWidth);
    int bitmapSize = bitmapHeader.BiWidth * bitmapHeader.BiHeight;
    char *byteArray = new char[rowSize];

    bitmapArray = new Color[bitmapSize];

    cout << "Bitmap size:" << bitmapSize << endl;
    cout << "Row Size:" << rowSize << endl;
    cout << "Padding:" << padding << endl;

    if (colorPalleteExists)
    {
        for (int l = 0; l < bitmapHeader.BiHeight; l++)
        {
            file.read(byteArray, rowSize);

            for (int i = 0; i <= rowSize - padding; i++)
            {

                if (bitmapHeader.BiBitCount == 1)
                {
                    for (int j = 0; j < 8; j++)
                    {

                        u_char pixelValue = (byteArray[i] << j) >> 7;

                        bitmapArray[l * bitmapHeader.BiWidth + i + j] = getPixelFromPallete(pixelValue);
                    }
                }
                if (bitmapHeader.BiBitCount == 4)
                {
                    for (int j = 0; j < 2; j++)
                    {

                        u_char pixelValue = (byteArray[i] << j) >> 4;
                        bitmapArray[l * bitmapHeader.BiWidth + i + j] = getPixelFromPallete(pixelValue);
                    }
                }
                if (bitmapHeader.BiBitCount == 8)
                {

                    u_char pixelValue = byteArray[i];
                    bitmapArray[l * bitmapHeader.BiWidth + i] = getPixelFromPallete(pixelValue);
                }
            }
        }
    }
    else
    {

        for (int l = 0; l < bitmapHeader.BiHeight; l++)
        {
            file.read(byteArray, rowSize);
            for (int i = 0, j = 0; i <= rowSize - padding; i += (int)(bitmapHeader.BiBitCount / 8), j++)
            {
                Color p;
                if (bitmapHeader.BiBitCount == 24)
                {
                    p.value[0] = byteArray[i + 2];
                    p.value[1] = byteArray[i + 1];
                    p.value[2] = byteArray[i + 0];
                }
                else
                {
                    p.value[0] = byteArray[i + 2];
                    p.value[1] = byteArray[i + 1];
                    p.value[2] = byteArray[i + 0];
                    p.value[3] = byteArray[i + 3];
                }

                bitmapArray[l * bitmapHeader.BiWidth + j] = p;
            }
        }
    }

    originalBitmapArray = new Color[bitmapSize];
    std::memcpy(originalBitmapArray, bitmapArray, bitmapSize * sizeof(Color));
}

Color Bitmap::getPixelColorAtPosition(const int l, const int c) const
{

    int idx = (height - 1 - l) * width + c;
    return bitmapArray[idx];
}

Int2 Bitmap::getPixelPositionOnScreen(const int l, const int c) const
{
    int newC = (c * cos(imageRotation) + l * sin(imageRotation));
    int newL = ((-c * sin(imageRotation)) + l * cos(imageRotation));
    Int2 pos = {newC, newL};
    return pos;
}

void Bitmap::scaleImage(const float scale)
{
    int oldHeight = this->height;
    int oldWidth = this->width;
    this->height = oldHeight * scale;
    this->width = oldWidth * scale;
    Color *newBitmapArray = new Color[height * width];
    for (int l = 0; l < height; l++)
    {
        for (int c = 0; c < width; c++)
        {
            int oldL = floor(l * (1 / scale));
            int oldC = floor(c * (1 / scale));
            int oldIdx = (oldHeight - 1 - oldL) * oldWidth + oldC;
            Color color = bitmapArray[oldIdx];

            int idx = (height - 1 - l) * width + c;
            newBitmapArray[idx] = color;
        }
    }
    if (bitmapArray != NULL)
    {
        delete[] bitmapArray;
        bitmapArray = NULL;
    }

    bitmapArray = newBitmapArray;
}

void Bitmap::flipImageInX()
{
    for (int l = 0; l < height; l++)
    {
        for (int c = 0; c < width / 2; c++)
        {
            int newIdx = (height - 1 - l) * width + (width - 1 - c);
            int idx = (height - 1 - l) * width + c;
            Color tmp = bitmapArray[idx];
            bitmapArray[idx] = bitmapArray[newIdx];
            bitmapArray[newIdx] = tmp;
        }
    }
}

void Bitmap::flipImageInY()
{
    for (int l = 0; l < height / 2; l++)
    {
        for (int c = 0; c < width; c++)
        {
            int newIdx = l * width + c;
            int idx = (height - 1 - l) * width + c;
            Color tmp = bitmapArray[idx];
            bitmapArray[idx] = bitmapArray[newIdx];
            bitmapArray[newIdx] = tmp;
        }
    }
}

void Bitmap::rotateImage(const float angle)
{
    this->imageRotation += angle;
}

void Bitmap::convertImageToGrayScale()
{
    for (int l = 0; l < height; l++)
    {
        for (int c = 0; c < width; c++)
        {
            int idx = (height - 1 - l) * width + c;

            float grayScaleColor = bitmapArray[idx].value[0] * 0.299 + bitmapArray[idx].value[1] * 0.587 + bitmapArray[idx].value[2] * 0.114;
            Color color;
            color.value[0] = grayScaleColor;
            color.value[1] = grayScaleColor;
            color.value[2] = grayScaleColor;
            bitmapArray[idx] = color;
        }
    }
}

int *Bitmap::getHistogramForChannel(const Channel c) const
{
    int *histogram = new int[256];
    for (int i = 0; i < 256; i++)
    {
        histogram[i] = 0;
    }
    for (int i = 0; i < width * height; i++)
    {
        histogram[(int)bitmapArray[i].value[c]] += 1;
    }
    return histogram;
}

void Bitmap::resetImage()
{
    if (bitmapArray != NULL)
    {
        delete[] bitmapArray;
        bitmapArray = NULL;
    }

    bitmapArray = new Color[bitmapHeader.BiHeight * bitmapHeader.BiWidth];
    memcpy(bitmapArray, originalBitmapArray, sizeof(Color) * bitmapHeader.BiHeight * bitmapHeader.BiWidth);
    this->height = bitmapHeader.BiHeight;
    this->width = bitmapHeader.BiWidth;
    this->imageRotation = 0;
}
