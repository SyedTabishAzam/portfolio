#pragma once
#include "Shape.h"

/** Rect class **/

class Rect : public Shape
{
private:
    Point bottomRight;
public:
    Rect(Point&, Point&);
    void SetBottomRight(int, int);
    const Point& GetBottomRight();
    void Draw(BITMAP* );
};

