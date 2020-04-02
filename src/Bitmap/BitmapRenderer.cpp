#include "BitmapRenderer.h"
#include "../Canvas/gl_canvas2d.h"
#include <iostream>

void BitmapRenderer::render()
{
    if(!isActive) return;
    for (int l = 0; l < bitmap->height; l++)
    {
        for (int c = 0; c < bitmap->width; c++)
        {
            Int2 pos = bitmap->getPixelPositionOnScreen(l, c);
            Color rgba = bitmap->getPixelColorAtPosition(l, c);

            color((float)rgba.value[0] / 255,
                  (float)rgba.value[1] / 255,
                  (float)rgba.value[2] / 255);

            point(pos.x + position.x, pos.y + position.y);
        }
    }
}

BitmapRenderer::BitmapRenderer(Bitmap *bitmap)
{
    this->bitmap = bitmap;
    this->isActive = true;
}
