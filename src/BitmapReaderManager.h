#ifndef BITMAPREADERMANAGER_H
#define BITMAPREADERMANAGER_H

#include "Button/Button.h"
#include "Histogram/HistogramRenderer.h"
#include "Bitmap/BitmapRenderer.h"

class BitmapRendererManager
{
public:
private:
    Bitmap *bitmap;
    BitmapRenderer *bitmapRenderer;
    HistogramRenderer *histogramRenderer;
    Button *grayscaleButton;
    Button *flipXButton;
    Button *flipYButton;
    Button *rotateButton;
    Button *scaleButton;
    Button *resetButton;
    Button *histogramButton;

    BitmapReaderManager();
}

#endif