#include <GL/glut.h>
#include <GL/freeglut_ext.h> //callback da wheel do mouse.
#include <string>
#include <iostream>

#include "gl_canvas2d.h"
#include "Bitmap.h"

int screenWidth = 500, screenHeight = 500;

Bitmap *bitmap;

void render()
{

   for (int l = 0; l < bitmap->height; l++)
   {
      for (int c = 0; c < bitmap->width; c++)
      {
         Color *rgba = bitmap->getPixelColorAtPosition(l, c);
         Int2 pos = bitmap->getPixelPositionOnScreen(l, c);
         //Default image
         color((float)rgba->value[0] / 255,
               (float)rgba->value[1] / 255,
               (float)rgba->value[2] / 255);

         point(pos.x + 100, pos.y + 100);

         // //Red channel image
         // color((float)rgba->value[0] / 255,
         //       0,
         //       0);
         // point(c + 50 + bitmap->width + 5, l + 50);
         // //Green channel image
         // color(0,
         //       (float)rgba->value[1] / 255,
         //       0);
         // point(c + 50 + bitmap->width * 2 + 5, l + 50);
         // //Blue channel image
         // color(0,
         //       0,
         //       (float)rgba->value[2] / 255);
         //point(c + 50 + bitmap->width * 3 + 5, l + 50);

         // cout << "R " << bitmap->bitmapArray[idx]->pixel[0] << " B " << bitmap->bitmapArray[idx]->pixel[1] << " G " << bitmap->bitmapArray[idx]->pixel[2];
      }
   }
}

void keyboard(int key)
{
   // printf("\nTecla: %d", key);
}

void keyboardUp(int key)
{
   //printf("\nLiberou: %d", key);
}

void mouse(int button, int state, int wheel, int direction, int x, int y)
{
   //printf("\nmouse %d %d %d %d %d %d", button, state, wheel, direction, x, y);
}

int main(void)
{
   initCanvas(&screenWidth, &screenHeight, "Bitmap reader");

   bitmap = new Bitmap("/home/menegais1/Documents/Projects/ComputerGraphics/Study/BitmapReader/src/test_boy.bmp");
 //  bitmap->convertImageToGrayScale();
   runCanvas();
}
