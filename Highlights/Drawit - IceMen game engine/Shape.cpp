#include"Shape.h"

/** Default Constructor **/
Shape::Shape()
{

}

/** Overloaded Constructor **/
Shape::Shape(const Point& position)
{
    this->position = position;
}

/** Destructor **/
Shape::~Shape()
{

}


/** Returns the class type value **/
int Shape::GetType()
{
    return type;
}

/** Sets position of the object**/
void Shape::SetPosition(const Point& position)
{
    this->position = position;
}

/** Gets position of the object**/
const Point& Shape::GetPosition()
{
    return position;
}

/** Will be overridden by Rect class **/
const Point& Shape::GetBottomRight()
{
    return position;
}

/** Will be overridden by Circle class **/
int Shape::GetRadius()
{
    return 0;
}
