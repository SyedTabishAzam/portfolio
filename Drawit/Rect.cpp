#include"Rect.h"

/** Overloaded constructor uses base class's constructor to initialize **/
Rect::Rect(Point& position, Point& bottomRight) : Shape(position)
{
    this->bottomRight  = bottomRight;
    type = 2;
}

void Rect::SetBottomRight(int x, int y)
{
    bottomRight.x = x;
    bottomRight.y = y;
}

const Point& Rect::GetBottomRight()
{
    return bottomRight;
}

/** Draws the rectangle **/
void Rect::Draw(BITMAP* buffer)
{

    rectfill(buffer, position.x, position.y, bottomRight.x, bottomRight.y, makecol(255, 255, 255));
}

