#pragma once

#include "Point.h"
#include "Turret.h"

class Ship{
    private:
        Point position;     //object of type POINT is made
        BITMAP* image;      //a pointer with allegro's inner type BITMAP is made
        Turret turret[2];   //object of type TURRET is made as an array, since there are 2 instances of this object
    public:
        Ship(){}            //Constructor
        ~Ship();            // De-constructor
        void Initialize(BITMAP* , BITMAP*, float ,float );  //other forward declarations
        void SetPosition(float ,float );
        void Draw(BITMAP* ,float);

};
