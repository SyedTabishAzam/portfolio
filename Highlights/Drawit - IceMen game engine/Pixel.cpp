#include"Pixel.h"

/** Overloaded constructor uses base class's constructor to initialize **/
Pixel::Pixel(Point& position) : Shape(position)
{
    type = 1;
    image = load_bitmap("Images/enem.bmp",NULL);
}

/** Draws the pixel **/
void Pixel::Draw(BITMAP* buffer)
{
     masked_blit(image,buffer,0,0,position.x,position.y,50,42);
}

