#pragma once
#include "Shape.h"

/** Pixel class **/

class Pixel : public Shape
{
private:
    BITMAP* image;
public:
    Pixel(Point&);
    void Draw(BITMAP* );
};

