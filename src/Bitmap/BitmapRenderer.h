#ifndef BITMAP_RENDERER_H
#define BITMAP_RENDERER_H

#include "../Base/IRender.h"
#include "../Base/IKeyboard.h"
#include "../Base/IMouse.h"
#include "Bitmap.h"
#include "../Utilities.h"
class BitmapRenderer : public IRender, public IKeyboard, public IMouse
{
public:
    void render() override;
    void keyboard(int key) override;
    void keyboardUp(int key) override;
    void mouse(int button, int state, int wheel, int direction, int x, int y) override;
    BitmapRenderer(Bitmap *bitmap);
    Int2 position;

private:
    const Bitmap *bitmap;
};

#endif
