#include"Shape.h"

/** Default Constructor **/
Shape::Shape()
{
    alive = true;
}

/** Default Constructor **/
Shape::Shape(const Point& position, const Color& color)
{
    this->position = position;
    this->color = color;
}

/** Overloaded Constructor **/
Shape::~Shape()
{

}

int Shape::GetRadius()
{
    return 0;
}

void Shape::CPosition(int pos)
{
    if(pos==0)
    {

        position.y = position.y - 5;
    }
    else
    {

        position.y = position.y + 5;
    }
}
/** Destructor **/
void Shape::SetColor(const Color& color)
{
    this->color = color;
}

/** Returns color as an integer value **/
int Shape::GetColor()
{
    return makecol(color.red, color.green, color.blue);
}

/** Sets position **/
void Shape::SetPosition(const Point& position)
{
    this->position = position;
}

Point Shape::GetPosition()
{
    return position;
}

string Shape::GetType()
{
    return type;
}

const Point& Shape::GetBottomRight()
{
    return position;
}

int Shape::GetLength()
{

}

int Shape::GetBreadth()
{

}

