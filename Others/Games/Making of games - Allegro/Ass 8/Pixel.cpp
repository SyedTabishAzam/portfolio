#include"Pixel.h"

/** Overloaded constructor uses base class's constructor to initialize **/
Pixel::Pixel(Point& position, Color& color) : Shape(position, color)
{
    alive = true;
    type = "p";
}

/** Draws the Pixel **/
void Pixel::Draw(BITMAP* buffer)
{   //using line to draw a pixel serves the purpose
    line(buffer, position.x, position.y, position.x,position.y, GetColor());
}


