#ifndef BITMAP_RENDERER_H
#define BITMAP_RENDERER_H

#include "../Base/CanvasObject.h"
#include "../Utilities.h"
#include "Bitmap.h"
class BitmapRenderer : public CanvasObject
{
public:
    void render() override;
    BitmapRenderer(Bitmap *bitmap);

private:
    const Bitmap *bitmap;
};

#endif
