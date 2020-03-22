#ifndef UTILITIES_H
#define UTILITIES_H

enum Channel
{
    Red = 0,
    Green = 1,
    Blue = 2,
    Alpha = 3
};

class Color
{
public:
    u_char value[4];
};

typedef struct int2
{
    int x;
    int y;
} Int2;

#endif