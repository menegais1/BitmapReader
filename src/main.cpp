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
         int idx = (bitmap->height - 1 - l) * bitmap->width + c;
         color((float)bitmap->bitmapArray[idx]->pixel[0] / 255,
               (float)bitmap->bitmapArray[idx]->pixel[1] / 255,
               (float)bitmap->bitmapArray[idx]->pixel[2] / 255);
         // cout << "R " << bitmap->bitmapArray[idx]->pixel[0] << " B " << bitmap->bitmapArray[idx]->pixel[1] << " G " << bitmap->bitmapArray[idx]->pixel[2];
         point(c + 50, l + 50);
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

   bitmap = new Bitmap("/home/menegais1/Documents/Projects/ComputerGraphics/Study/BitmapReader/src/test_1.bmp");
   
   runCanvas();
}
