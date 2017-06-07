#include"Viper.h"
#include<iostream>


Viper::Viper(BITMAP* image, int frame_width, int frame_height, Point position) : Plane(image, frame_width, frame_height, position)
{
    type=2;
    SetHealth(30);
    CURRENT_STATE = MIDDLE;
    velx = 1;
    vely = 1;
}

Viper::Viper(BITMAP* image, int frame_width, int frame_height, int x, int y) : Plane(image, frame_width, frame_height, x, y)
{
    type=2;
    SetHealth(30);
    CURRENT_STATE = MIDDLE;
    velx = 1;
    vely = 1.5f;
}

Viper::~Viper()
{
    std::cout<<"Viper Destroyed"<<endl;
}


void Viper::Move()
{
    if(this->position.x < target->GetPosition().x - target->GetFrameWidth())
    {
        velx = 1;
        CURRENT_STATE = LEFT;
        Move(velx,vely);
    }
    else if(this->position.x > target->GetPosition().x + target->GetFrameWidth())
    {
        velx = 1;
        CURRENT_STATE = RIGHT;
        Move(-velx,vely);
    }
    else
    {
        CURRENT_STATE = MIDDLE;
        velx = velx * 0.925f;
        Move(velx, vely);
    }
}

void Viper::Move(float x, float y)
{
    position.x = position.x + x;
    position.y = position.y + y;
    if(position.y > SCREEN_H + GetFrameHeight())
        SetAlive(false);
}

void Viper::SetTarget(Object* object)
{
    target = object;
}

void Viper::Draw(BITMAP* buffer, bool debug)
{
    if(CURRENT_STATE == LEFT)
        masked_blit(image, buffer, 320, 0, position.x, position.y, frame_width,frame_height);
    else if(CURRENT_STATE == MIDDLE)
        masked_blit(image, buffer, 256, 0, position.x, position.y, frame_width,frame_height);
    else if(CURRENT_STATE == RIGHT)
        masked_blit(image, buffer, 192, 0, position.x, position.y, frame_width,frame_height);
    if(debug == true)
    {
        line(buffer, position.x,position.y, position.x+frame_width,position.y, makecol(255, 0, 0));
        line(buffer, position.x+frame_width,position.y, position.x+frame_width,position.y+frame_height, makecol(255, 0, 0));
        line(buffer, position.x,position.y+frame_height, position.x+frame_width,position.y+frame_height, makecol(255, 0, 0));
        line(buffer, position.x,position.y+frame_height, position.x,position.y, makecol(255, 0, 0));
    }
}

