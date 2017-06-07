#include"Circle.h"
#include <iostream>
using namespace std;
/** Overloaded constructor uses base class's constructor to initialize **/
Circle::Circle(Point& position, Color& color, int radius) : Shape(position, color)
{
    this->radius  = radius;
    alive = true;
    type = "c";
}

/** Sets radius of the current circle **/
void Circle::SetRadius(int radius)
{
    this->radius = radius;
}

int Circle::GetRadius()
{
    return radius;
}

/** Draws the circle **/
void Circle::Draw(BITMAP* buffer)
{
    circlefill(buffer, position.x, position.y, radius, GetColor());
}
