#include "KeyboardManager.h"
#include <vector>
#include <iostream>
using namespace std;

KeyboardManager::KeyboardManager()
{
    keyboardEvents = new vector<IKeyboard *>();
}

void KeyboardManager::keyboard(int key) const
{

    for (int i = 0; i < keyboardEvents->size(); i++)
    {
        keyboardEvents->at(i)->keyboard(key);
    }
}

void KeyboardManager::keyboardUp(int key) const
{

    for (int i = 0; i < keyboardEvents->size(); i++)
    {
        keyboardEvents->at(i)->keyboardUp(key);
    }
}

int KeyboardManager::registerKeyboardEvent(IKeyboard *keyboardEvent)
{
    keyboardEvents->push_back(keyboardEvent);
    return keyboardEvents->size() - 1;
}

IKeyboard *KeyboardManager::unregisterKeyboardEvent(int keyboardEventId)
{
    IKeyboard *keyboardEvent = keyboardEvents->at(keyboardEventId);
    keyboardEvents->erase(keyboardEvents->begin() + keyboardEventId);
    return keyboardEvent;
}
