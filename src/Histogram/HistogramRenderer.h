///Class responsible for rendering an histogram, it receives a int vector
///And render the histogram in a bar graph, the color given will be interpolated
///to give a smooth gradient for each histogram value

#ifndef HISTOGRAM_RENDERER_H
#define HISTOGRAM_RENDERER_H

#include "../Utilities.h"
#include "../Base/CanvasObject.h"

class HistogramRenderer : public CanvasObject
{
public:
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