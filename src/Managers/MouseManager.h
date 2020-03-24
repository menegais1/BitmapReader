#ifndef MOUSE_MANAGER_H
#define MOUSE_MANAGER_H

#include "../Base/IMouse.h"
#include <vector>
class MouseManager
{
public:
    MouseManager();
    void mouse(int button, int state, int wheel, int direction, int x, int y) const;
    int registerMouseEvent(IMouse *mouseEvent);
    IMouse *unregisterMouseEvent(int MouseEventId);

private:
    std::vector<IMouse *> *mouseEvents;
};

#endif
