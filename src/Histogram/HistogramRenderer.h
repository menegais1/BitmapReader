#ifndef HISTOGRAM_RENDERER_H
#define HISTOGRAM_RENDERER_H

#include "../Utilities.h"
#include "../Base/CanvasObject.h"

class HistogramRenderer : public CanvasObject
{
public:
    bool isActive;
    Int2 position;
    Int2 scale;
    Float3 backgroundColor;
    Float3 lineColor;
    void render() override;
    void setHistogram(int *histogram);
    HistogramRenderer(Int2 position, Int2 scale, Float3 backgroundColor, Float3 lineColor);

private:
    int *histogram;
    float greatest;
};

#endif