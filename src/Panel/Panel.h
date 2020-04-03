#ifndef PANEL_H
#define PANEL_H

#include "../Base/CanvasObject.h"
#include "../Utilities.h"
#include <vector>
class Panel : public CanvasObject
{
public:
    Float3 backgroundColor;
    std::vector<CanvasObject *> children;
    Panel(std::vector<CanvasObject *> &children);
    Panel();
    Panel(Float2 position, Float2 scale, Float3 backgroundColor);
    void setActive(bool isActive) override;
};

#endif
