///Main program file, used to instantiate all screen elements,
///register buttons callbacks, call bitmap manipulation functions and
///load the bitmap file from the Images folder.

#ifndef BITMAPREADERMANAGER_H
#define BITMAPREADERMANAGER_H

#include "Button/Button.h"
#include "Histogram/HistogramPanel.h"
#include "Bitmap/BitmapRenderer.h"
#include "Panel/Panel.h"
#include "Slider/Slider.h"
#include "Label/Label.h"
#include <string>
class BitmapReaderManager : public Panel
{
public:
    BitmapReaderManager(std::string fileName);

private:
    Bitmap *bitmap;
    BitmapRenderer *bitmapRenderer;
    HistogramPanel *histogramPanel;
    Button *grayscaleButton;
    Button *rChannelButton;
    Button *gChannelButton;
    Button *bChannelButton;
    Button *flipXButton;
    Button *flipYButton;
    Button *scaleButton;
    Button *resetButton;
    Button *histogramButton;
    Label *rotationLabel;
    Slider *rotationSlider;

    void initializeBitmap(std::string fileName);
    void initializeButtons();
    void initializeHistogram();
};

#endif
