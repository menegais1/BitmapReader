#ifndef KEYBOARD_MANAGER_H
#define KEYBOARD_MANAGER_H

#include "IKeyboard.h"
#include <vector>
class KeyboardManager
{
public:
    KeyboardManager();
    void keyboard(int key) const;
    void keyboardUp(int key) const;
    int registerKeyboardEvent(IKeyboard *keyboardEvent);
    IKeyboard *unregisterKeyboardEvent(int keyboardEventId);

private:
    std::vector<IKeyboard *> *keyboardEvents;
};

#endif
