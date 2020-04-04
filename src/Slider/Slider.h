#ifndef SLIDER_H
#define SLIDER_H

#include "../Base/CanvasObject.h"
#include "../Utilities.h"
#include <functional>
#include <vector>
class Slider : public CanvasObject
{
public:
    float handleSize;
    Float2 handlePosition;
    Float3 handleColor;

    Float3 backgroundColor;

    float tolerance;
    float minValue;
    float maxValue;
    float curValue;
    int steps;

    Slider(Float2 position, Float2 scale, Float3 backgroundColor, float handleSize, Float3 handleColor);
    void initializeSlider(float minValue, float maxValue, int steps, float tolerance);
    void render() override;
    void mouse(int button, int state, int wheel, int direction, int x, int y) override;
    void addOnValueChangedListener(std::function<void(float value)> listener);
    void notifyOnValueChangedListeners();

private:
    float stepAmount; 
    bool isDragging;
    float screenStep; 
    int lastMouseState;
    Int2 prevMousePosition;
    std::vector<std::function<void(float value)>> onValueChangedListeners;
};

#endif
