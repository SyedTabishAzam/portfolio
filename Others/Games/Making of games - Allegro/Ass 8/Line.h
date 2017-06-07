#pragma once
#include "Shape.h"

/** Line class **/

class Line : public Shape
{
private:
    int xc;
    int yc;
    Point bottomRight;
public:
    Line(Point&, Color&);
    void SetCoord(int,int);
    void CPosition(int);
    void SetLength(int);
    void SetBottomRight(int, int);
    const Point& GetBottomRight();
    Point GetPosition();
    void Draw(BITMAP*);
};


