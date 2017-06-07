#include "square.h"

Square::Square(){
    //
    }

Square:: Square(BITMAP* img){
            image = img;
    }

Square::~Square(){
    delete[] image;
    image = NULL;
    }

void Square::Initialize(BITMAP* img){
        image = img;
    }

void Square::Draw(BITMAP* buffer,int r,int c){
        position.x =30 + (r * 64); // offset 30 to include border horizontal
        position.y=30 + (c * 64);   //offset 30 to include border veritcal
        blit(image,buffer,64*((r+c)%2),0,position.x,position.y,64,64);  //extract sprite, different sprite depending on even or odd number of square
}
