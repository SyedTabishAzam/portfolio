#pragma once
#include "allegro.h"
#include "point.h"
#include "piece.h"

class Square
{
private:
    point position;
    bool occupied;
    BITMAP* image;
    piece pis;
    int piecenum;
public:
    Square();
    ~Square();
    int getPiece();
    void setPiece(int);
    Square(int , int, BITMAP*,BITMAP*);
    void setPosition(int, int);
    point* getPosition();
    void setImage(BITMAP*);
    void setOccupied(bool);
    bool getOccupied();
    void draw(BITMAP*);
};

