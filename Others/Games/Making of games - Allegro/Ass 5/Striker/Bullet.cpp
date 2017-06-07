#include"Bullet.h"
#include<iostream>


Bullet::Bullet(BITMAP* image, int frame_width, int frame_height, Point position) : Plane(image, frame_width, frame_height, position)
{
    type=1;
    SetHealth(300);
    velx = 0;
    vely = 8.0f;
}

Bullet::Bullet(BITMAP* image, int frame_width, int frame_height, int x, int y) : Plane(image, frame_width, frame_height, x, y)
{
    type=1;
    SetHealth(15);
    velx = 0;
    vely = -8.0f;
}

Bullet::~Bullet()
{
    std::cout<<"Bullet Destroyed"<<endl;
}


void Bullet::Move()
{
    Move(velx, vely);
}

void Bullet::Move(float x, float y)
{
    position.x = position.x + x;
    position.y = position.y + y;
    if(position.y < 0 - GetFrameHeight())
        SetAlive(false);
}


void Bullet::Draw(BITMAP* buffer, bool debug)
{
    masked_blit(image, buffer, 0, 128, position.x, position.y, frame_width,frame_height);

    if(debug == true)
    {
        line(buffer, position.x,position.y, position.x+frame_width,position.y, makecol(255, 0, 0));
        line(buffer, position.x+frame_width,position.y, position.x+frame_width,position.y+frame_height, makecol(255, 0, 0));
        line(buffer, position.x,position.y+frame_height, position.x+frame_width,position.y+frame_height, makecol(255, 0, 0));
        line(buffer, position.x,position.y+frame_height, position.x,position.y, makecol(255, 0, 0));
    }
}


