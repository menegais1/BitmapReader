#include "HistogramRenderer.h"
#include "../Utilities.h"
#include "../Canvas/gl_canvas2d.h"
void HistogramRenderer::render()
{
    if (!isActive)
        return;
    color(backgroundColor.x, backgroundColor.y, backgroundColor.z);
    rectFill(position.x, position.y, position.x + scale.x, position.y + scale.y);
    color(lineColor.x, lineColor.y, lineColor.z);
    line(position.x + 10, position.y + 10, position.x + 10, position.y + scale.y - 10);
    line(position.x + 10, position.y + 10, position.x + scale.x - 10, position.y + 10);

    if (histogram != nullptr)
    {
        for (int i = 0; i < 255; i++)
        {
            Int2 leftDownCorner = {(position.x + 10 + i), position.y + 10};
            Int2 rightUpCorner = {(position.x + 10 + i + 1), (position.y + 10) + histogram[i + 1] % (scale.y - 10)};
            rectFill(leftDownCorner.x, leftDownCorner.y, rightUpCorner.x, rightUpCorner.y);
        }
    }
}
void HistogramRenderer::setHistogram(int *histogram)
{
    this->histogram = histogram;
}
HistogramRenderer::HistogramRenderer(Int2 position, Int2 scale, Float3 backgroundColor, Float3 lineColor) : position(position),
                                                                                                            scale(scale),
                                                                                                            backgroundColor(backgroundColor),
                                                                                                            lineColor(lineColor)
{
    this->isActive = true;
}
