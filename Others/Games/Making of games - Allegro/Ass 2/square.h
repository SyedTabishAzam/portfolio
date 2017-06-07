#pragma once
#include "Point.h"
#include "allegro.h"
class Square{
    private:
        Point position;
        BITMAP* image;

    public:
        Square();
        Square(BITMAP*);
        void Initialize(BITMAP* );
        ~Square();
        void Draw(BITMAP*,int,int);

};

