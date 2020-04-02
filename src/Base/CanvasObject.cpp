#include "CanvasObject.h"
#include "../Managers/GlobalManager.h"
#include "../Utilities.h"
#include <iostream>
void CanvasObject::keyboard(int key)
{
}
void CanvasObject::keyboardUp(int key)
{
}
void CanvasObject::mouse(int button, int state, int wheel, int direction, int x, int y)
{
}
void CanvasObject::render()
{
}
CanvasObject::CanvasObject()
{
    objectId = GlobalManager::getInstance()->registerObject(this);
    //std::cout << objectId << std::endl;
    isActive = true;
    position = {0, 0};
    scale = {1, 1};
}
