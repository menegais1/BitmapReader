#include "BitmapRenderer.h"
#include "../Canvas/gl_canvas2d.h"
#include <iostream>

void BitmapRenderer::render()
{
    for (int l = 0; l < bitmap->height; l++)
    {
        for (int c = 0; c < bitmap->width; c++)
        {
            Int2 pos = bitmap->getPixelPositionOnScreen(l, c);
            Color *rgba = bitmap->getPixelColorAtPosition(l, c);

            color((float)rgba->value[0] / 255,
                  (float)rgba->value[1] / 255,
                  (float)rgba->value[2] / 255);

            point(pos.x + position.x, pos.y + position.y);
        }
    }
}

void BitmapRenderer::keyboard(int key)
{
    std::cout << "Down: " << key << std::endl;
}

void BitmapRenderer::keyboardUp(int key)
{
    std::cout << "UP: " << key << std::endl;
}

BitmapRenderer::BitmapRenderer(Bitmap *bitmap)
{
    this->bitmap = bitmap;
}

void BitmapRenderer::mouse(int button, int state, int wheel, int direction, int x, int y)
{
    std::cout << x << " " << y << std::endl;
}
