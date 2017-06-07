#pragma once
#include"point.h"
#include"allegro.h"
//class of piece, methods explained in cpp file
class piece
{
private:
    point position;
    BITMAP* image;
    bool king;
public:
    bool white;
    piece();
    void initPiece(int, int, BITMAP*, bool);
    ~piece();
    void moveTo(point*);
    point* getPosition();
    void setKing(bool);
    bool isKing();
    void draw(BITMAP*);
};
