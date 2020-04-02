#ifndef BITMAPREADERMANAGER_H
#define BITMAPREADERMANAGER_H

#include "Button/Button.h"
#include "Histogram/HistogramRenderer.h"
#include "Bitmap/BitmapRenderer.h"

class BitmapReaderManager
{
public:
    BitmapReaderManager();

private:
    Bitmap *bitmap;
    BitmapRenderer *bitmapRenderer;

    HistogramRenderer *red;
    HistogramRenderer *blue;
    HistogramRenderer *green;
    HistogramRenderer *grayscale;

    Button *grayscaleButton;
    Button *rChannelButton;
    Button *gChannelButton;
    Button *bChannelButton;
    Button *flipXButton;
    Button *flipYButton;
    Button *rotateButton;
    Button *scaleButton;
    Button *resetButton;
    Button *histogramButton;

    void registerButton(Button *b);
    void initializeManagers();
    void initializeBitmap();
    void initializeButtons();
    void initializeHistogram();
};

#endif
