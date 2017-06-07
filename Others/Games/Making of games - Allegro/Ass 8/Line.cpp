#include"Line.h"

/** Overloaded constructor uses base class's constructor to initialize **/
Line::Line(Point& position, Color& color) : Shape(position, color)
{
    //Sets alive to true, indicating object has to be shown on screen
    this->bottomRight = bottomRight;
    alive = true;
    type="l";
}

/** Sets radius of the current Line **/
void Line::SetCoord(int x,int y)
{   //Sets x y coordinates of the line
    this->xc = x;
    this->yc = y;
}

void Line::CPosition(int pos)
{   //Change position according to the coordinates, and pos specifies if it has to move up or down
    if(pos==0)
    {
        yc = yc -5;
        position.y=position.y-5;
    }
    else
    {
        yc = yc + 5;
        position.y = position.y +5;
    }
}

/** Draws the Line **/
void Line::Draw(BITMAP* buffer)
{
    line(buffer, position.x, position.y, xc, yc, GetColor());
    bottomRight.x = xc;
    bottomRight.y = yc;
}

void Line::SetBottomRight(int x, int y)
{

}

/** Getting the second point **/
const Point& Line::GetBottomRight()
{
    return bottomRight;
}

Point Line::GetPosition()
{
    return position;
}

