#pragma once
#include "Shape.h"

/** Circle class **/

class Circle : public Shape
{
private:
    int radius;
public:
    Circle(Point&, Color&, int );
    void SetRadius(int);
    void Draw(BITMAP* );
    int GetRadius();
};
