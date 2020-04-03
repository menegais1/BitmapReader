#include "HistogramPanel.h"
#include "HistogramRenderer.h"
#include "../Button/Button.h"

HistogramPanel::HistogramPanel(int *red, int *green, int *blue, int *grayscale) : Panel({0, 0}, {0, 0}, {0, 0, 0})
{
    initialize();
    setHistograms(red, green, blue, grayscale);
}

HistogramPanel::HistogramPanel()
{
    initialize();
}

void HistogramPanel::initialize()
{
    this->red = new HistogramRenderer({125, 400}, {270, 100}, {0, 0, 0}, {1, 0, 0});
    this->green = new HistogramRenderer({125, 300}, {270, 100}, {0, 0, 0}, {0, 1, 0});
    this->blue = new HistogramRenderer({125, 200}, {270, 100}, {0, 0, 0}, {0, 0, 1});
    this->grayscale = new HistogramRenderer({125, 100}, {270, 100}, {0, 0, 0}, {0.5, 0.5, 0.5});
    closePanel = new Button({250, 40}, {70, 30}, {1, 1, 1}, "Close", {0, 0, 0});
    closePanel->addListener([this] { this->setActive(false); });
    this->children.push_back(red);
    this->children.push_back(green);
    this->children.push_back(blue);
    this->children.push_back(grayscale);
    this->children.push_back(closePanel);
    this->setActive(false);
}
void HistogramPanel::setHistograms(int *red, int *green, int *blue, int *grayscale)
{
    this->red->setHistogram(red);
    this->green->setHistogram(green);
    this->blue->setHistogram(blue);
    this->grayscale->setHistogram(grayscale);
}
