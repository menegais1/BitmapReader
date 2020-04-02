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
#include "Histogram/HistogramRenderer.h"
using namespace std;
int screenWidth = 500, screenHeight = 500;

RenderManager *renderManager = new RenderManager();
KeyboardManager *keyboardManager = new KeyboardManager();
MouseManager *mouseManager = new MouseManager();

int test = 0;
void render()
{
   color(1, 1, 1);
   point(1, test);
   point(2, test);
   point(3, test);
   test++;
   if (test == 100)
      test = 0;
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

   Bitmap *bitmap = new Bitmap("/home/menegais1/Documents/Projects/ComputerGraphics/Study/BitmapReader/src/normal_1.bmp");

   BitmapRenderer *bitmapRenderer1 = new BitmapRenderer(bitmap);
   bitmapRenderer1->position = {125, 50};
   renderManager->registerRenderer(bitmapRenderer1);

   Button *grayscale = new Button({25, 400}, {100, 40}, {1, 1, 1}, "Grayscale", {0, 0, 0});
   grayscale->addListener([&bitmap] { bitmap->convertImageToGrayScale(); });
   mouseManager->registerMouseEvent(grayscale);
   renderManager->registerRenderer(grayscale);

   Button *flipX = new Button({130, 400}, {100, 40}, {1, 1, 1}, "Flip X", {0, 0, 0});
   flipX->addListener([&bitmap] { bitmap->flipImageInX(); });
   mouseManager->registerMouseEvent(flipX);
   renderManager->registerRenderer(flipX);

   Button *flipY = new Button({240, 400}, {100, 40}, {1, 1, 1}, "Flip Y", {0, 0, 0});
   flipY->addListener([&bitmap] { bitmap->flipImageInY(); });
   mouseManager->registerMouseEvent(flipY);
   renderManager->registerRenderer(flipY);

   Button *rotate = new Button({350, 400}, {100, 40}, {1, 1, 1}, "Rotate", {0, 0, 0});
   rotate->addListener([&bitmap] { bitmap->rotateImage(3.14 / 2.0); });
   mouseManager->registerMouseEvent(rotate);
   renderManager->registerRenderer(rotate);

   Button *scale = new Button({25, 450}, {100, 40}, {1, 1, 1}, "Scale 1/2", {0, 0, 0});
   scale->addListener([&bitmap] { bitmap->scaleImage(0.5); });
   mouseManager->registerMouseEvent(scale);
   renderManager->registerRenderer(scale);

   Button *reset = new Button({130, 450}, {100, 40}, {1, 1, 1}, "Reset", {0, 0, 0});
   reset->addListener([&bitmap] { bitmap->resetImage(); });
   mouseManager->registerMouseEvent(reset);
   renderManager->registerRenderer(reset);

   HistogramRenderer *red = new HistogramRenderer({100, 100}, {270, 100}, {0, 0, 0}, {1, 0, 0});
   red->setHistogram(bitmap->getHistogramForChannel(Channel::Red));
   renderManager->registerRenderer(red);

   HistogramRenderer *green = new HistogramRenderer({100, 200}, {270, 100}, {0, 0, 0}, {0, 1, 0});
   green->setHistogram(bitmap->getHistogramForChannel(Channel::Green));
   renderManager->registerRenderer(green);

   HistogramRenderer *blue = new HistogramRenderer({100, 300}, {270, 100}, {0, 0, 0}, {0, 0, 1});
   blue->setHistogram(bitmap->getHistogramForChannel(Channel::Blue));
   renderManager->registerRenderer(blue);
   runCanvas();
}
