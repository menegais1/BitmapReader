#ifndef CANVAS_OBJECT_H
#define CANVAS_OBJECT_H

#include "IMouse.h"
#include "IKeyboard.h"
#include "IRender.h"
#include "../Utilities.h"
class CanvasObject : public IRender, public IKeyboard, public IMouse
{
public:
    Float2 position;
    Float2 scale;
    void keyboard(int key) override;
    void keyboardUp(int key) override;
    void mouse(int button, int state, int wheel, int direction, int x, int y) override;
    void render() override;
    CanvasObject();
    virtual void setActive(bool isActive);
    bool getActive();
    bool checkIfCanExecuteCallback();
protected:
    bool isActive;
    int objectId;

private:
    bool lastActiveState;
};
#endif
