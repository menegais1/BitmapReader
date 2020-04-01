#include <GL/glut.h>
#include <GL/freeglut_ext.h> //callback da wheel do mouse.
#include <string>
#include <iostream>

#include "Canvas/gl_canvas2d.h"
#include "Bitmap/Bitmap.h"
#include "Utilities.h"
#include "Bitmap/BitmapRenderer.h"
#include "Managers/RenderManager.h"
#include "Managers/KeyboardManager.h"
#include "Managers/MouseManager.h"
#include "Button/Button.h"
using namespace std;
int screenWidth = 500, screenHeight = 500;

RenderManager *renderManager = new RenderManager();
KeyboardManager *keyboardManager = new KeyboardManager();
MouseManager *mouseManager = new MouseManager();
void render()
{
   renderManager->render();
}

void keyboard(int key)
{
   keyboardManager->keyboard(key);
}

void keyboardUp(int key)
{
   keyboardManager->keyboardUp(key);
}

void mouse(int button, int state, int wheel, int direction, int x, int y)
{
   mouseManager->mouse(button, state, wheel, direction, x, y);
}

int main(void)
{
   initCanvas(&screenWidth, &screenHeight, "Bitmap reader");

   Bitmap *bitmap = new Bitmap("/home/menegais1/Documents/Projects/ComputerGraphics/Study/BitmapReader/src/landscape.bmp");

   BitmapRenderer *bitmapRenderer1 = new BitmapRenderer(bitmap);
   bitmapRenderer1->position = {100, 100};
   cout << renderManager->registerRenderer(bitmapRenderer1) << endl;
   Button *button = new Button({100, 100}, {100, 100}, {1, 1, 1}, "teste", {0, 0, 0});
   mouseManager->registerMouseEvent(button);
   renderManager->registerRenderer(button);
   button->addListener([&bitmap] { bitmap->convertImageToGrayScale(); });
   button->addListener([] { cout << "Hello word 2" << endl; });
   runCanvas();
}
