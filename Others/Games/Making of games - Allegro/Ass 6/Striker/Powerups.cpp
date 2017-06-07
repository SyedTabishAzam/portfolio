#include "Powerups.h"
#include <iostream>
using namespace std;

Powerups::Powerups(BITMAP* img,int randpup,Point pos)
{
    this->image=img;
    position=pos;
    alive=true;
    //random number between 0-2 inclusive is generated
    powerup = rand()%3;
    type=21 + powerup;  //type of powerup starts from 21

}

Powerups::~Powerups()
{
    cout<<"Powerups Class Destroyed"<<endl;
}

void Powerups::Move()
{   //move in down direction
    position.y = position.y +1;
    //if it gets bellow screen, declare it not alive
    if(position.y>SCREEN_H)
        SetAlive(false);
}

void Powerups::Draw(BITMAP* buffer,bool debug)
{   //draw powerup
    masked_blit(image,buffer,powerup*32,733,position.x,position.y,32,32);
}
