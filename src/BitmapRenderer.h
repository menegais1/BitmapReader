#ifndef BITMAP_RENDERER_H
#define BITMAP_RENDERER_H

#include "IRender.h"
#include "IKeyboard.h"
#include "Bitmap.h"
#include "Utilities.h"
class BitmapRenderer : public IRender, public IKeyboard
{
public:
    void render() override;
    void keyboard(int key) override;
    void keyboardUp(int key) override;
    BitmapRenderer(Bitmap *bitmap);
    Int2 position;

private:
    const Bitmap *bitmap;
};

#endif
