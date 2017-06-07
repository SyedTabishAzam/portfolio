#pragma once
#include "Shape.h"

/** Square class **/

class Square : public Shape
{
private:
    int length;
    int breadth;
    Point bottomRight;
public:
    Square(Point&, Color&, int ,int);
    void SetLength(int);
    void SetBreadth(int);
    int GetLength();
    int GetBreadth();
    void Draw(BITMAP*);
    Point GetPosition();
    void SetBottomRight(int, int);
    const Point& GetBottomRight();
    void CPosition(int);
};

