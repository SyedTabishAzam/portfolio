#pragma once
#include "Point.h"
#include "allegro.h"

class Turret{
private:
    Point position;     //Makes an object of type POINT to store coordinates of turret
    BITMAP* image;      //Make Pointer of type BITMAP as image, to save turret image

public:
    Turret(){}          //Constructor
    ~Turret();          //De-constructor
    bool top;           //boolen to determine if the turret is on top or bottom
    void Initialize(BITMAP* , float ,float );   //Prototypes
    void SetPosition(float, float);
    void Draw(BITMAP*,float);

};
