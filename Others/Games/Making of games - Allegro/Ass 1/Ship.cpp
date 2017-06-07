#include "Ship.h"

Ship::~Ship(){
//
}
void Ship::Initialize(BITMAP* si, BITMAP* ti, float sx,float sy){
        image= si;      //loads image of ship in variable named image

        turret[0].top=false;        //specifies if the turret is on top or bottom of ship
        turret[0].Initialize(ti,sx,sy); //initializes turret, passing the turret image to it as args, and position of ship
        turret[1].top=true;         //second turret is not to be placed on top
        turret[1].Initialize(ti,sx,sy); //initializes second turret

        this->SetPosition(sx,sy);       //access the setposition of the same class, and sets the position to sx and sy

    }

void Ship::SetPosition(float x ,float y){

        position.x = x;             //object of type POINT named position is provided with x and y coordinates
        position.y = y;
        turret[0].SetPosition(x,y); //makes sure that turret's position is also changed everytime the ships position is changed
        turret[1].SetPosition(x,y);
    }

void Ship::Draw(BITMAP* buffer,float rot){

        draw_sprite(buffer, image, position.x,position.y);  //draws the ship on position x and y, as updated by setPosition function
        turret[0].Draw(buffer,rot);     //every time the ship is drawn, the turrets on the ship are also drawn
        turret[1].Draw(buffer,rot);
        //P.S THE SHIP DRAWN WONT BE ON THE CENTER OF THE SCREEN, SINCE THE SHIP'S OWN WIDTH ISN'T TAKEN TO ACCOUNT PURPOSLY
    }
