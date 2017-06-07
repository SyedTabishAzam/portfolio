#include"Bullet.h"
#include "math.h"
#include<iostream>


Bullet::Bullet(BITMAP* image, int frame_width, int frame_height,int typ, Point position,int targetx,int targety) : Plane(image, frame_width, frame_height, position)
{
    //type is passed to typ
    type=typ;
    SetHealth(15); //health of bullet is 15
    if(type==9) //if type is 9 (missile)
        SetHealth(30);  //health is 30
    velx = 0;
    vely = 8.0f;
    this->targetx = targetx;
    this->targety= targety;
    smokecount = 0;
}

Bullet::Bullet(BITMAP* image, int frame_width, int frame_height,int typ, int x, int y,int targetx,int targety) : Plane(image, frame_width, frame_height, x, y)
{
    type=typ;
    SetHealth(15);
    if(type==9)
        SetHealth(30);
    velx = 0;
    vely = -8.0f;
    this->targetx = targetx ;
    this->targety= targety;
    smokecount = 0;
}

Bullet::~Bullet()
{
    std::cout<<"Bullet Destroyed"<<endl;
}

void Bullet::Move()
{
    if(int(type/10)==0)
    {//if the bullet type is below 10 (player or fighter's bullet)
        if(type==9 && smokecount<26)
        {   //counter to delay the smoke image
            smokecount = smokecount + 1;
        }
        else
        {
            Move(velx, vely);
        }

           //move it simply in one direction)
    }
    else if(int(type/10)==1)
    {   //if the bullet type is above 10 (enemy bullet)

        int angle = atan2(targety-position.y,targetx-position.x) ;  //determine the angle that is between bullet and player

        velx = velx + (cos(angle) * 0.097); //move bullet towards the player slowly
        Move(velx,-vely);
    }

}

void Bullet::Move(float x, float y)
{


    position.x = position.x+x;
    position.y = position.y + y;
    if(int(type/10)==0)
    {//for players bullet, if bullet goes above screen, declare its alive as false
        if(position.y < 0 - GetFrameHeight())
        {
            SetAlive(false);
            smokecount = 0;
        }

    }
    else
    {   //for enemies bullet, if it goes below screen, declare it as not alive
        if(position.y>SCREEN_H)
            SetAlive(false);
    }
}


void Bullet::Draw(BITMAP* buffer, bool debug)
{
    if(type==9)
    {//this is to create smoke that follows the missile bullet
        masked_blit(image, buffer, 783, 128, position.x, position.y, frame_width,frame_height);
        if(smokecount<=5)       //for every sp count uptil +5, one frame is displayed. this ensures frames doesnt run too fast
            masked_blit(image, buffer, 270, 687, position.x-24, position.y, 46,46);
        else if(smokecount<=10)
            masked_blit(image, buffer, 316, 687, position.x-24, position.y, 46,46);
        else if(smokecount<=15)
            masked_blit(image, buffer, 362, 687, position.x-24, position.y, 46,46);
        else if(smokecount<=20)
            masked_blit(image, buffer, 408, 687, position.x-24, position.y, 46,46);
        else if(smokecount<=25)
            masked_blit(image, buffer, 408, 687, position.x-24, position.y, 46,46);


    }
    else    //else simply draw the bullet according to the type (the greate the type, the greate the column in the bullet section of image)
        masked_blit(image, buffer, 16*((type%10)-2), 128, position.x, position.y, frame_width,frame_height);

    if(debug == true)
    {
        if(type==11)
            line(buffer, position.x,position.y, targetx,targety, makecol(255, 0, 0));
        line(buffer, position.x,position.y, position.x+frame_width,position.y, makecol(255, 0, 0));
        line(buffer, position.x+frame_width,position.y, position.x+frame_width,position.y+frame_height, makecol(255, 0, 0));
        line(buffer, position.x,position.y+frame_height, position.x+frame_width,position.y+frame_height, makecol(255, 0, 0));
        line(buffer, position.x,position.y+frame_height, position.x,position.y, makecol(255, 0, 0));
    }
}

