#include "Turret.h"

Turret::~Turret(){
    //
}
void Turret::Initialize(BITMAP* ti, float tix,float tiy){
        image = ti;     //sets the image of turret
        this->SetPosition(tix,tiy);     //Set position takes the position of ship since we know turret would always be inside ships
    }

void Turret::SetPosition(float tx,float ty){
        if(this->top){                  //checks if the turret is to be placed on top of ship or at bottom
            position.x = tx + 9;        //constant values changing the turret position on ship accordingly
            position.y = ty + 65;
            }
        else{
            position.x=tx+9;
            position.y=ty+195;
            }
    }

void Turret::Draw(BITMAP* buffer,float rot){
       //this function basically draws the turret image and rotates it to rot degree
        if(!this->top){
            rotate_sprite(buffer, image, position.x, position.y, itofix(130+rot));  //if turret is not on top, starting position is altered so that turret is facing the bottom of ship, and then rotated accordingly
            }
        else
            {
            rotate_sprite(buffer, image, position.x, position.y, itofix(rot)); // if turret is on top, it is facing the front of ship
            }
    }
