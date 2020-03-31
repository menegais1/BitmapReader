#include "Utilities.h"
bool isPointInsideBounds(Int2 point, Int2 position, Int2 scale)
{
    return point.x < position.x + scale.x && point.x > position.x && point.y < position.y + scale.y && point.y > position.y;
}
