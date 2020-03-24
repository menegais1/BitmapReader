#include <GL/glut.h>
#include <GL/freeglut_ext.h> //callback da wheel do mouse.
#include <string>
#include <iostream>

#include "gl_canvas2d.h"
#include "Bitmap.h"
#include "Utilities.h"
#include "BitmapRenderer.h"
#include "RenderManager.h"
#include "KeyboardManager.h"
#include "MouseManager.h"

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

   Bitmap *bitmap = new Bitmap("/home/menegais1/Documents/Projects/ComputerGraphics/Study/BitmapReader/src/test.bmp");
   Bitmap *bitmap2 = new Bitmap("/home/menegais1/Documents/Projects/ComputerGraphics/Study/BitmapReader/src/test_1.bmp");

   BitmapRenderer *bitmapRenderer1 = new BitmapRenderer(bitmap);
   BitmapRenderer *bitmapRenderer2 = new BitmapRenderer(bitmap2);
   bitmapRenderer2->position = {100, 100};
   bitmapRenderer1->position = {200, 100};
   cout << renderManager->registerRenderer(bitmapRenderer1) << endl;
   cout << renderManager->registerRenderer(bitmapRenderer2) << endl;
   keyboardManager->registerKeyboardEvent(bitmapRenderer1);
   mouseManager->registerMouseEvent(bitmapRenderer1);
   bitmap2->flipImageInX();
   runCanvas();
}
