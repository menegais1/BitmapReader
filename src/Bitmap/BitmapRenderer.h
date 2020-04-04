///Class responsible for rendering the bitmap, allow the bitmap to
///be moved around the screen when holding and dragging the mouse on top of it

#ifndef BITMAP_RENDERER_H
#define BITMAP_RENDERER_H

#include "../Base/CanvasObject.h"
#include "../Utilities.h"
#include "Bitmap.h"
class BitmapRenderer : public CanvasObject
{
public:
    void render() override;
    void mouse(int button, int state, int wheel, int direction, int x, int y) override;
    BitmapRenderer(Bitmap *bitmap);

private:
    const Bitmap *bitmap;
    bool isDragging;
    int lastMouseState;
    Int2 prevMousePosition;
};

#endif
