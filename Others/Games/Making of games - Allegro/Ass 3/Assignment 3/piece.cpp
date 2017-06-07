#include "piece.h"
#include "iostream"

using namespace std;
piece::piece(){

}
void piece::initPiece(int x, int y, BITMAP* img, bool w){
    point* pos;                                             //initializes piece, gives its x and y (row and column) as positions
    pos->x=x;
    pos->y=y;
    moveTo(pos);                                            //pass the pos to position through setter method
    image = img;
    white = w;                                              //bool to determine if the initialized piece is white or black
}

piece::~piece(){

}

void piece::moveTo(point* pos){
    position.x = 30+((pos->x) *64);                             //30 offset for border, plus the rows * 64 for x axis
    position.y = 30+((pos->y) *64);                             //since 64 is the width of image, same goes for y axis
}

point* piece::getPosition(){
    return &position;                                           //returns position pointer
}

void piece::setKing(bool king){
    this->king = king;                                          //sets the piece as king if it reaches the border
}

bool piece::isKing(){
    return this->king;                                          //return the status of the piece
}

void piece::draw(BITMAP* buffer){

    point* p = getPosition();
    if(white){                                                  //if the piece is white then do the following
        if (isKing()==true){                                    //if the piece has reached the king's position then do the following
            masked_blit(image,buffer,64,128,p->x,p->y,64,64);   //extract the sprite for white king from the image
        }
        else{
            masked_blit(image,buffer,64,64,p->x,p->y,64,64);    //else, just extract sprite for white from image
        }
    }
    else{                                                       //do exactly the same as above for black piece.
        if (isKing()==true){
            masked_blit(image,buffer,0,128,p->x,p->y,64,64);
        }
        else{
            masked_blit(image,buffer,0,64,p->x,p->y,64,64);
        }
    }

}
