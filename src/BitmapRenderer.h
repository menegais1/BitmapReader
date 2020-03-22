#ifndef BITMAP_RENDERER_H
#define BITMAP_RENDERER_H

#include "IRender.h"
#include "Bitmap.h"
#include "Utilities.h"
class BitmapRenderer : public IRender
{
public:
    void render() override;
    BitmapRenderer(Bitmap* bitmap);
    Int2 position;
private:
    const Bitmap *bitmap;
};

#endif
