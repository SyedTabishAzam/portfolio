#include"Square.h"
#include <iostream>

using namespace std;
/** Overloaded constructor uses base class's constructor to initialize **/
Square::Square(Point& position, Color& color, int length,int breadth) : Shape(position, color)
{
    alive = true;
    this->bottomRight  = bottomRight;
    this->length  = 0;
    this->breadth = 0;
    type= "r";
}

/** Sets radius of the current Square **/
void Square::SetLength(int length)
{   //Sets length, so that the length can change in real time using this function
    this->length = length;
}

void Square::SetBreadth(int breadth)
{
    this->breadth = breadth;
}


int Square::GetLength()
{
    return length;
}

int Square::GetBreadth()
{
    return breadth;
}

/** Draws the Square **/
void Square::Draw(BITMAP* buffer)
{
    rectfill(buffer, length, breadth, position.x,position.y, GetColor());
}

void Square::CPosition(int p)
{ //If p = 0, we know we have to move up, hence reduce 5 from every y coordinate of square
    if(p==0)
    {
        breadth = breadth - 5;
        position.y = position.y - 5;
    }
    else
    {
        breadth = breadth + 5;
        position.y = position.y + 5;
    }
}

void Square::SetBottomRight(int x, int y)
{
    bottomRight.x = x;
    bottomRight.y = y;
}

const Point& Square::GetBottomRight()
{
    return bottomRight;
}

Point Square::GetPosition()
{
    return position;
}
