#ifndef BITMAP_H
#define BITMAP_H

#include <string>
#include <fstream>
#include <iostream>

using namespace std;
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
        cout << "BfType:" << BfType << endl;
        cout << "BfSize:" << BfSize << endl;
        cout << "BfReser1:" << BfReser1 << endl;
        cout << "BfReser1:" << BfReser1 << endl;
        cout << "BfOffSetBits:" << BfOffSetBits << endl;
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
        cout << "BiSize:" << BiSize << endl;
        cout << "BiWidth:" << BiWidth << endl;
        cout << "BiHeight:" << BiHeight << endl;
        cout << "BiPlanes:" << BiPlanes << endl;
        cout << "BiBitCount:" << BiBitCount << endl;
        cout << "BiCompress:" << BiCompress << endl;
        cout << "BiSizeImag:" << BiSizeImag << endl;
        cout << "BiXPPMeter:" << BiXPPMeter << endl;
        cout << "BiYPPMeter:" << BiYPPMeter << endl;
        cout << "BiClrUsed:" << BiClrUsed << endl;
        cout << "BiClrImpor:" << BiClrImpor << endl;
    }
};

class ColorPallete
{
public:
    u_char Blue;
    u_char Green;
    u_char Red;
    u_char Reserved;
};

class Pixel
{
public:
    u_char pixel[4];
};

class Bitmap
{
public:
    string fileName;
    int width;
    int height;
    Pixel **bitmapArray;
    Bitmap(std::string fileName);

private:
    FileHeader *fileHeader;
    BitmapHeader *bitmapHeader;
    ColorPallete **colorPallete;
    bool colorPalleteExists;

    void openFile(string filename, fstream &file);
    void loadFileHeader(fstream &file);
    void loadBitmapHeader(fstream &file);
    bool checkColorPallete(fstream &file);
    void loadColorPallete(fstream &file);
    void loadImage(fstream &file);
    Pixel *getPixelFromPallete(u_char pixelValue);
};

Bitmap::Bitmap(string fileName)
{
    this->fileName = fileName;
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

    width = bitmapHeader->BiWidth;
    height = bitmapHeader->BiHeight;
}

void Bitmap::openFile(string filename, fstream &file)
{
    file.open(filename, fstream::in | fstream::binary);
}

void Bitmap::loadFileHeader(fstream &file)
{
    this->fileHeader = new FileHeader();
    file.read(reinterpret_cast<char *>(&fileHeader->BfType), 2);
    file.read(reinterpret_cast<char *>(&fileHeader->BfSize), 4);
    file.read(reinterpret_cast<char *>(&fileHeader->BfReser1), 2);
    file.read(reinterpret_cast<char *>(&fileHeader->BfReser2), 2);
    file.read(reinterpret_cast<char *>(&fileHeader->BfOffSetBits), 4);
}

void Bitmap::loadBitmapHeader(fstream &file)
{
    this->bitmapHeader = new BitmapHeader();
    file.read(reinterpret_cast<char *>(&bitmapHeader->BiSize), 4);
    file.read(reinterpret_cast<char *>(&bitmapHeader->BiWidth), 4);
    file.read(reinterpret_cast<char *>(&bitmapHeader->BiHeight), 4);
    file.read(reinterpret_cast<char *>(&bitmapHeader->BiPlanes), 2);
    file.read(reinterpret_cast<char *>(&bitmapHeader->BiBitCount), 2);
    file.read(reinterpret_cast<char *>(&bitmapHeader->BiCompress), 4);
    file.read(reinterpret_cast<char *>(&bitmapHeader->BiSizeImag), 4);
    file.read(reinterpret_cast<char *>(&bitmapHeader->BiXPPMeter), 4);
    file.read(reinterpret_cast<char *>(&bitmapHeader->BiYPPMeter), 4);
    file.read(reinterpret_cast<char *>(&bitmapHeader->BiClrUsed), 4);
    file.read(reinterpret_cast<char *>(&bitmapHeader->BiClrImpor), 4);
}

bool Bitmap::checkColorPallete(fstream &file)
{
    if (bitmapHeader->BiBitCount < 24)
        return true;
    return false;
}

void Bitmap::loadColorPallete(fstream &file)
{
    int palleteCount = pow(2, bitmapHeader->BiBitCount);
    colorPallete = (ColorPallete **)malloc(sizeof(ColorPallete *) * palleteCount);

    for (int i = 0; i < palleteCount; i++)
    {
        colorPallete[i] = new ColorPallete();
        file.read(reinterpret_cast<char *>(&colorPallete[i]->Blue), 1);
        file.read(reinterpret_cast<char *>(&colorPallete[i]->Green), 1);
        file.read(reinterpret_cast<char *>(&colorPallete[i]->Red), 1);
        file.read(reinterpret_cast<char *>(&colorPallete[i]->Reserved), 1);
    }
}

Pixel *Bitmap::getPixelFromPallete(u_char pixelValue)
{
    Pixel *p = new Pixel();
    p->pixel[0] = colorPallete[pixelValue]->Red;
    p->pixel[1] = colorPallete[pixelValue]->Green;
    p->pixel[2] = colorPallete[pixelValue]->Blue;
    p->pixel[3] = colorPallete[pixelValue]->Reserved;
    return p;
}
void Bitmap::loadImage(fstream &file)
{
    //file.seekg(fileHeader->BfOffSetBits, ios::beg);
    int rowSize = ceil((bitmapHeader->BiBitCount * bitmapHeader->BiWidth) / 32) * 4;
    int padding = rowSize - (bitmapHeader->BiBitCount / 8 * bitmapHeader->BiWidth);
    int bitmapSize = bitmapHeader->BiWidth * bitmapHeader->BiHeight;
    char *byteArray = (char *)malloc(rowSize);

    bitmapArray = (Pixel **)malloc(bitmapSize * sizeof(Pixel *));

    cout << "Bitmap size:" << bitmapSize << endl;
    cout << "Row Size:" << rowSize << endl;
    cout << "Padding:" << padding << endl;

    if (colorPalleteExists)
    {
        for (int l = 0; l < bitmapHeader->BiHeight; l++)
        {
            file.read(byteArray, rowSize);

            for (int i = 0; i <= rowSize - padding; i++)
            {

                if (bitmapHeader->BiBitCount == 1)
                {
                    for (int j = 0; j < 8; j++)
                    {

                        u_char pixelValue = (byteArray[i] << j) >> 7;

                        bitmapArray[l * bitmapHeader->BiWidth + i + j] = getPixelFromPallete(pixelValue);
                    }
                }
                if (bitmapHeader->BiBitCount == 4)
                {
                    for (int j = 0; j < 2; j++)
                    {

                        u_char pixelValue = (byteArray[i] << j) >> 4;
                        bitmapArray[l * bitmapHeader->BiWidth + i + j] = getPixelFromPallete(pixelValue);
                    }
                }
                if (bitmapHeader->BiBitCount == 8)
                {

                    u_char pixelValue = byteArray[i];
                    bitmapArray[l * bitmapHeader->BiWidth + i] = getPixelFromPallete(pixelValue);
                }
            }
        }
    }
    else
    {

        for (int l = 0; l < bitmapHeader->BiHeight; l++)
        {
            file.read(byteArray, rowSize);

            for (int i = 0, j = 0; i <= rowSize - padding; i += (int)(bitmapHeader->BiBitCount / 8), j++)
            {
                Pixel *p = new Pixel();
                if (bitmapHeader->BiBitCount == 24)
                {
                    p->pixel[0] = byteArray[i + 2];
                    p->pixel[1] = byteArray[i + 1];
                    p->pixel[2] = byteArray[i + 0];
                }
                else
                {
                    p->pixel[0] = byteArray[i + 2];
                    p->pixel[1] = byteArray[i + 1];
                    p->pixel[2] = byteArray[i + 0];
                    p->pixel[3] = byteArray[i + 3];
                }

                bitmapArray[l * bitmapHeader->BiWidth + j] = p;
            }
        }
    }
}
#endif
