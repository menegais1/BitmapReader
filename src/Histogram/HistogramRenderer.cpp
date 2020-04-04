#include "HistogramRenderer.h"
#include "../Utilities.h"
#include "../Canvas/gl_canvas2d.h"
#include <iostream>
using namespace std;
void HistogramRenderer::render()
{
    color(backgroundColor.x, backgroundColor.y, backgroundColor.z);
    rectFill(position.x, position.y, position.x + scale.x, position.y + scale.y);
    color(lineColor.x, lineColor.y, lineColor.z);
    line(position.x, position.y, position.x, position.y + scale.y - 10);
    line(position.x, position.y, position.x + scale.x - 10, position.y);

    if (histogram != nullptr)
    {

        for (int i = 0; i < 256; i++)
        {
            color(lineColor.x * ((i/256.0) + 0.1) , lineColor.y *((i/256.0)+ 0.1), lineColor.z * ((i/256.0)+ 0.1));
            Int2 leftDownCorner = {(position.x + 2 + i), position.y + 2};
            Int2 rightUpCorner = {(position.x + 2 + i + 1), (position.y + 2) + (histogram[i] / greatest) * scale.y};
            rectFill(leftDownCorner.x, leftDownCorner.y, rightUpCorner.x, rightUpCorner.y);
        }
    }
}
void HistogramRenderer::setHistogram(int *histogram)
{
    this->histogram = histogram;
    greatest = 0;
    for (int i = 0; i < 256; i++)
    {
        if (histogram[i] > greatest)
            greatest = histogram[i];
    }
}
HistogramRenderer::HistogramRenderer(Int2 position, Int2 scale, Float3 backgroundColor, Float3 lineColor) : CanvasObject(), position(position),
                                                                                                            scale(scale),
                                                                                                            backgroundColor(backgroundColor),
                                                                                                            lineColor(lineColor)
{
    histogram = nullptr;
}
