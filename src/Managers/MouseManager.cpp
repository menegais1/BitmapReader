#include "MouseManager.h"
#include <vector>
#include <iostream>
using namespace std;

MouseManager::MouseManager()
{
}

void MouseManager::mouse(int button, int state, int wheel, int direction, int x, int y) const
{

    for (int i = 0; i < mouseEvents.size(); i++)
    {
        mouseEvents[i]->mouse(button,state,wheel,direction,x,y);
    }
}

int MouseManager::registerMouseEvent(IMouse *mouseEvent)
{
    mouseEvents.push_back(mouseEvent);
    return mouseEvents.size() - 1;
}

IMouse *MouseManager::unregisterMouseEvent(int mouseEventId)
{
    IMouse *mouseEvent = mouseEvents[mouseEventId];
    mouseEvents.erase(mouseEvents.begin() + mouseEventId);
    return mouseEvent;
}
