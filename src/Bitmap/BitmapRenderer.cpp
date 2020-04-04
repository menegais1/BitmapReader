#include "BitmapRenderer.h"
#include "../Canvas/gl_canvas2d.h"
#include <iostream>

void BitmapRenderer::render()
{
    for (int l = 0; l < bitmap->height; l++)
    {
        for (int c = 0; c < bitmap->width; c++)
        {
            Float2 pos = bitmap->getPixelPositionOnScreen(l, c);
            Color rgba = bitmap->getPixelColorAtPosition(l, c);

            color((float)rgba.value[0] / 255,
                  (float)rgba.value[1] / 255,
                  (float)rgba.value[2] / 255);

            point(pos.x + position.x, pos.y + position.y);
        }
    }
}

void BitmapRenderer::mouse(int button, int state, int wheel, int direction, int x, int y)
{
    if (state != MouseState::None && button == MouseButton::Left)
    {
        this->lastMouseState = state;
        isDragging = false;
    }

    if (state == MouseState::None &&
        this->lastMouseState == MouseState::Down &&
        (isPointInsideBounds({x, y}, {position.x, position.y}, {bitmap->width, bitmap->height}) || isDragging) &&
        direction != 0)
    {
        isDragging = true;

        position.x += x - prevMousePosition.x;
        position.y += y - prevMousePosition.y;
    }

    prevMousePosition = {x, y};
}

BitmapRenderer::BitmapRenderer(Bitmap *bitmap) : CanvasObject()
{
    this->bitmap = bitmap;
    this->lastMouseState = MouseState::None;
}
