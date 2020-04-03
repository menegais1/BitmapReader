#include "BitmapReaderManager.h"
#include "Button/Button.h"
#include <cmath>
#include "Managers/GlobalManager.h"
#include "Panel/Panel.h"
#include "Histogram/HistogramPanel.h"

BitmapReaderManager::BitmapReaderManager() : Panel()
{

    bitmap = new Bitmap("/home/menegais1/Documents/Projects/ComputerGraphics/Study/BitmapReader/src/Images/test.bmp");
    bitmapRenderer = new BitmapRenderer(bitmap);
    bitmapRenderer->position = {125, 300};
     histogramPanel = new HistogramPanel();
    histogramPanel->closePanel->addListener([this] {
        this->setActive(true);
    });
    initializeButtons();
    children.push_back(bitmapRenderer);
    children.push_back(grayscaleButton);
    children.push_back(rChannelButton);
    children.push_back(gChannelButton);
    children.push_back(bChannelButton);
    children.push_back(flipXButton);
    children.push_back(flipYButton);
    children.push_back(rotateButton);
    children.push_back(scaleButton);
    children.push_back(histogramButton);
    children.push_back(resetButton);
}

void BitmapReaderManager::initializeManagers()
{
}
void BitmapReaderManager::initializeBitmap()
{
}
void BitmapReaderManager::initializeButtons()
{
    //Color Buttons
    grayscaleButton = new Button({340, 90}, {110, 30}, {1, 1, 1}, "Grayscale", {0, 0, 0});
    grayscaleButton->addListener([*this] { this->bitmap->convertImageToGrayScale(); });
    rChannelButton = new Button({230, 90}, {100, 30}, {1, 1, 1}, "R Channel", {0, 0, 0});
    rChannelButton->addListener([*this] { this->bitmap->convertToSingleChannel(Channel::Red); });
    gChannelButton = new Button({120, 90}, {100, 30}, {1, 1, 1}, "G Channel", {0, 0, 0});
    gChannelButton->addListener([*this] { this->bitmap->convertToSingleChannel(Channel::Green); });
    bChannelButton = new Button({10, 90}, {100, 30}, {1, 1, 1}, "B Channel", {0, 0, 0});
    bChannelButton->addListener([*this] { this->bitmap->convertToSingleChannel(Channel::Blue); });

    //Image operations Buttons
    flipXButton = new Button({340, 50}, {100, 30}, {1, 1, 1}, "Flip X", {0, 0, 0});
    flipXButton->addListener([*this] { this->bitmap->flipImageInX(); });
    flipYButton = new Button({230, 50}, {100, 30}, {1, 1, 1}, "Flip Y", {0, 0, 0});
    flipYButton->addListener([*this] { this->bitmap->flipImageInY(); });
    rotateButton = new Button({120, 50}, {100, 30}, {1, 1, 1}, "Rotate 90", {0, 0, 0});
    rotateButton->addListener([*this] { this->bitmap->rotateImage(M_PI / 2.0); });
    scaleButton = new Button({10, 50}, {100, 30}, {1, 1, 1}, "Scale 1/2", {0, 0, 0});
    scaleButton->addListener([*this] { this->bitmap->scaleImage(0.5); });

    histogramButton = new Button({10, 10}, {100, 30}, {1, 1, 1}, "Histogram", {0, 0, 0});
    histogramButton->addListener([this] {
        this->setActive(false);
        this->histogramPanel->setActive(true);
        int *red = this->bitmap->getHistogramForChannel(Channel::Red);
        int *green = this->bitmap->getHistogramForChannel(Channel::Green);
        int *blue = this->bitmap->getHistogramForChannel(Channel::Blue);
        this->bitmap->convertImageToGrayScale();
        int *grayscale = this->bitmap->getHistogramForChannel(Channel::Red);
        this->bitmap->resetImage();
        this->histogramPanel->setHistograms(red, green, blue, grayscale);
    });
    resetButton = new Button({120, 10}, {100, 30}, {1, 1, 1}, "Reset", {0, 0, 0});
    resetButton->addListener([*this] { this->bitmap->resetImage(); });
}

void BitmapReaderManager::registerButton(Button *b)
{
}
