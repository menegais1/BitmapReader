#ifndef BITMAP_RENDERER_H
#define BITMAP_RENDERER_H

#include "../Base/IRender.h"
#include "../Utilities.h"
#include "Bitmap.h"
class BitmapRenderer : public IRender
{
public:
    bool isActive;
    Int2 position;
    void render() override;
    BitmapRenderer(Bitmap *bitmap);

private:
    const Bitmap *bitmap;
};

#endif
