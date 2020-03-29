#include "KeyboardManager.h"
#include <vector>
#include <iostream>
using namespace std;

KeyboardManager::KeyboardManager()
{
}

void KeyboardManager::keyboard(int key) const
{

    for (int i = 0; i < keyboardEvents.size(); i++)
    {
        keyboardEvents[i]->keyboard(key);
    }
}

void KeyboardManager::keyboardUp(int key) const
{

    for (int i = 0; i < keyboardEvents.size(); i++)
    {
        keyboardEvents[i]->keyboardUp(key);
    }
}

int KeyboardManager::registerKeyboardEvent(IKeyboard *keyboardEvent)
{
    keyboardEvents.push_back(keyboardEvent);
    return keyboardEvents.size() - 1;
}

IKeyboard *KeyboardManager::unregisterKeyboardEvent(int keyboardEventId)
{
    IKeyboard *keyboardEvent = keyboardEvents[keyboardEventId];
    keyboardEvents.erase(keyboardEvents.begin() + keyboardEventId);
    return keyboardEvent;
}
