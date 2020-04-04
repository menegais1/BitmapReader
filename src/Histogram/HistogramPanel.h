///Inherit from the Panel class and is responsible for grouping the
///histograms in a single object, as well as a button to deactivate this object

#ifndef HISTOGRAM_PANEL_H
#define HISTOGRAM_PANEL_H

#include "../Utilities.h"
#include "../Panel/Panel.h"
#include "HistogramRenderer.h"
#include "../Button/Button.h"

class HistogramPanel : public Panel
{
public:
    HistogramRenderer *red;
    HistogramRenderer *green;
    HistogramRenderer *blue;
    HistogramRenderer *grayscale;
    Button *closePanel;
    HistogramPanel(int *red, int *green, int *blue, int *grayscale);
    HistogramPanel();
    void setHistograms(int *red, int *green, int *blue, int *grayscale);
    void initialize();
};

#endif
