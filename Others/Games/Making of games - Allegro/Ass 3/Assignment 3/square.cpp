#include "square.h"

Square::Square(){

    }


Square::~Square(){

    }

void Square::setPosition(int r, int c){
    position.x = 30 + (r * 64);   //offset 30 to include border horizontal
    position.y = 30 + (c * 64);   //offset 30 to include border vertical
    }

point* Square::getPosition(){
    return &position;
    }

void Square::setImage(BITMAP* img){
    image = img;
    }

void Square::setOccupied(bool ocup){
    occupied = ocup;
    }

bool Square::getOccupied(){
    return occupied;
    }

void Square::setPiece(int num){
    piecenum = num;
}

int Square::getPiece(){
    return piecenum;
}
void Square::draw(BITMAP* buffer){
    point* p = this->getPosition();
    int r = ((p->x)-30)/64;
    int c = ((p->y)-30)/64;
    blit(image,buffer,64*((r+c)%2),0,p->x,p->y,64,64);  //extract sprite, different sprite depending on even or odd number of square
    }
