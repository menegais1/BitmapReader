#ifndef BUTTON_H
#define BUTTON_H

#include "../Base/IMouse.h"
#include "../Base/IRender.h"
#include "../Utilities.h"
#include <vector>
#include <functional>
class Button : public IMouse, public IRender
{
public:
    Int2 position;
    Int2 scale;
    Float3 backgroundColor;
    Float3 textColor;
    std::string title;
    Button(Int2 position, Int2 scale, Float3 backgroundColor, std::string title, Float3 textColor);
    void mouse(int button, int state, int wheel, int direction, int x, int y) override;
    void render() override;
    void addListener(std::function<void()> listener);

private:
    std::vector<std::function<void()>> onClickListeners;
    void notifyOnClickListeners();
};

#endif
