#include "BitmapReaderManager.h"
#include "Button/Button.h"
#include <cmath>
#include <iostream>
#include "Managers/GlobalManager.h"
#include "Panel/Panel.h"
#include "Histogram/HistogramPanel.h"
#include "Slider/Slider.h"
#include "Label/Label.h"

BitmapReaderManager::BitmapReaderManager(std::string fileName) : Panel()
{

    initializeBitmap(fileName);
    initializeHistogram();
    initializeButtons();

    children.push_back(bitmapRenderer);
    children.push_back(grayscaleButton);
    children.push_back(rChannelButton);
    children.push_back(gChannelButton);
    children.push_back(bChannelButton);
    children.push_back(flipXButton);
    children.push_back(flipYButton);
    children.push_back(histogramButton);
    children.push_back(resetButton);
    children.push_back(rotationLabel);
    children.push_back(rotationSlider);
    children.push_back(scaleLabel);
    children.push_back(scaleSlider);
}

void BitmapReaderManager::initializeBitmap(std::string fileName)
{
    bitmap = new Bitmap(fileName);
    this->bitmap->nearestNeighbourRotation(0);

    bitmapRenderer = new BitmapRenderer(bitmap);
    bitmapRenderer->position = {125, 300};
}
void BitmapReaderManager::initializeHistogram()
{

    histogramPanel = new HistogramPanel();
    histogramPanel->closePanel->addListener([this] {
        this->setActive(true);
    });
}

void BitmapReaderManager::initializeButtons()
{
    //Color Buttons
    grayscaleButton = new Button({340, 90}, {110, 30}, {1, 1, 1}, "Grayscale", {0, 0, 0});
    grayscaleButton->addListener([*this] {
        this->bitmap->convertImageToGrayScale();
        this->bitmap->applyTransformations(true, true, true);
    });
    rChannelButton = new Button({230, 90}, {100, 30}, {1, 1, 1}, "R Channel", {0, 0, 0});
    rChannelButton->addListener([*this] {
        this->bitmap->convertToSingleChannel(Channel::Red);
        this->bitmap->applyTransformations(true, true, true);
    });
    gChannelButton = new Button({120, 90}, {100, 30}, {1, 1, 1}, "G Channel", {0, 0, 0});
    gChannelButton->addListener([*this] {
        this->bitmap->convertToSingleChannel(Channel::Green);
        this->bitmap->applyTransformations(true, true, true);
    });
    bChannelButton = new Button({10, 90}, {100, 30}, {1, 1, 1}, "B Channel", {0, 0, 0});
    bChannelButton->addListener([*this] {
        this->bitmap->convertToSingleChannel(Channel::Blue);
        this->bitmap->applyTransformations(true, true, true);
    });

    //Image operations Buttons
    flipXButton = new Button({340, 50}, {100, 30}, {1, 1, 1}, "Flip X", {0, 0, 0});
    flipXButton->addListener([*this] {
        this->bitmap->flipImageInX();
        this->bitmap->applyTransformations(true, true, true);
    });
    flipYButton = new Button({230, 50}, {100, 30}, {1, 1, 1}, "Flip Y", {0, 0, 0});
    flipYButton->addListener([*this] {
        this->bitmap->flipImageInY();
        this->bitmap->applyTransformations(true, true, true);
    });

    rotationLabel = new Label({130, 74}, {80, 10}, {1, 1, 1}, {0, 0, 0}, "Rotation");
    rotationSlider = new Slider({130, 60}, {80, 10}, {1, 0, 0}, 10, {1, 1, 1});
    rotationSlider->initializeSlider(0.0, M_PI, 100, 1.3);
    rotationSlider->setCurrentValue(0);
    rotationSlider->addOnValueChangedListener([*this](float curValue) {
        this->bitmap->nearestNeighbourRotation(curValue);
        this->bitmap->applyTransformations(true, true, true);
    });

    scaleLabel = new Label({10, 74}, {80, 10}, {1, 1, 1}, {0, 0, 0}, "Scale");
    scaleSlider = new Slider({10, 60}, {80, 10}, {1, 0, 0}, 10, {1, 1, 1});
    scaleSlider->initializeSlider(1 / 32.0, 4, 20, 1.3);
    scaleSlider->setCurrentValue(1.0);
    scaleSlider->addOnValueChangedListener([*this](float curValue) {
        this->bitmap->scaleImage(curValue);
        this->bitmap->applyTransformations(true, true, true);
    });

    histogramButton = new Button({10, 10}, {100, 30}, {1, 1, 1}, "Histogram", {0, 0, 0});
    histogramButton->addListener([this] {
        this->setActive(false);
        this->histogramPanel->setActive(true);
        this->bitmap->resetImageToDefault();
        int *red = this->bitmap->getHistogramForChannel(Channel::Red);
        int *green = this->bitmap->getHistogramForChannel(Channel::Green);
        int *blue = this->bitmap->getHistogramForChannel(Channel::Blue);
        this->bitmap->convertImageToGrayScale();
        this->bitmap->applyTransformations(false, false, true);
        int *grayscale = this->bitmap->getHistogramForChannel(Channel::Red);
        this->bitmap->resetImageToDefault();
        this->histogramPanel->setHistograms(red, green, blue, grayscale);
    });

    resetButton = new Button({120, 10}, {100, 30}, {1, 1, 1}, "Reset", {0, 0, 0});
    resetButton->addListener([*this] {
        this->bitmap->resetImageToDefault();
        this->bitmap->applyTransformations(false, true, false);
        this->scaleSlider->setCurrentValue(1);
        this->rotationSlider->setCurrentValue(0);
    });
}
