#ifndef HISTOGRAM_H
#define HISTOGRAM_H

#include "../Utilities.h"
#include "../Base/IRender.h"

class Histogram : public IRender
{
public:
    Int2 position;
    Int2 scale;
    Float3 backgroundColor;
    Float3 lineColor;
    void render() override;
    void setHistogram(int *histogram);
    Histogram(Int2 position, Int2 scale, Float3 backgroundColor, Float3 lineColor);

private:
    int *histogram;
};

#endif