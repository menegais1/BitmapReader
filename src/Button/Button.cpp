#include "../Base/IMouse.h"
#include "../Utilities.h"
#include <vector>
#include <functional>
#include "Button.h"
#include "../Canvas/gl_canvas2d.h"
#include <iostream>

using namespace std;

Button::Button(Int2 position, Int2 scale, Float3 backgroundColor, string title,Float3 textColor) :
position(position),
                                                                scale(scale),
                                                                backgroundColor(backgroundColor),
                                                                title(title),
                                                                textColor(textColor)
{
}
void Button::mouse(int button, int state, int wheel, int direction, int x, int y)
{
   if(button == MouseButton::Left && state == MouseState::Down){
       if(isPointInsideBounds({x,y}, position,scale)){
           notifyOnClickListeners();
       }
   }
}
void Button::render()
{
    color(backgroundColor.x, backgroundColor.y, backgroundColor.z);
    rectFill(position.x, position.y, position.x + scale.x, position.y + scale.y);
    color(textColor.x,textColor.y,textColor.z);
    text(position.x + scale.x / 4, position.y + scale.y / 2, title.c_str());
}

void Button::notifyOnClickListeners()
{
    cout << "ButtonClicked" << endl;
}

void Button::addListener(std::function<void()> listener)
{
}
