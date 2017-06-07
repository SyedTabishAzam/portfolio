#pragma once
#include "Shape.h"

/** Pixel class **/

class Pixel : public Shape
{
private:

public:
    Pixel(Point&, Color&);
    void Draw(BITMAP*);
};

