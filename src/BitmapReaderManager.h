#ifndef BITMAPREADERMANAGER_H
#define BITMAPREADERMANAGER_H

#include "Button/Button.h"
#include "Histogram/HistogramPanel.h"
#include "Bitmap/BitmapRenderer.h"
#include "Panel/Panel.h"
class BitmapReaderManager : public Panel
{
public:
    BitmapReaderManager();

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
