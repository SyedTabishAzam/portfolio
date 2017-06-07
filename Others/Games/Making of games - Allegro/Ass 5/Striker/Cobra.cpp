#include"Cobra.h"
#include<iostream>


Cobra::Cobra(BITMAP* image, int frame_width, int frame_height, Point position) : Plane(image, frame_width, frame_height, position)
{
    type=2; //type is set to 2
    SetHealth(30);  //health is set to 30
    CURRENT_STATE = MIDDLE; //start state is Middle
    velx = 1;
    vely = 1;
}

Cobra::Cobra(BITMAP* image, int frame_width, int frame_height, int x, int y) : Plane(image, frame_width, frame_height, x, y)
{
    type=2;
    SetHealth(30);
    CURRENT_STATE = MIDDLE;
    velx = 1;
    vely = 1.5f;
}

Cobra::~Cobra()
{
    std::cout<<"Cobra Destroyed"<<endl;
}


void Cobra::Move()
{
    //if the position of our plane, gets near 10 points of the cobra (enemy) plane, this condition is met
    if((int(this->position.x)<int(target->GetPosition().x))&&(int(this->position.x)>int(target->GetPosition().x)-10))
    {
        int moverand = rand()%2; //a random value generator between 0-1 inclusive
        if (moverand==0)    //if value generated is 0
        {
            velx = 8;       //velx is a positive number
            CURRENT_STATE = RIGHT;  //set the state to right
            velx = velx * 0.925f;
            Move(velx, vely);   //move by factor of velx
        }
        else    //if value generated is 1
        {
            velx=-8;        //velx is negative
            CURRENT_STATE=LEFT; //state set to left
            velx = velx * 0.925f;
            Move(velx, vely);   //move by factor of velx , i.e negative (Towards left)
        }
    }
    else
    {  //if the planes are not near each other
        if(int(velx)==0)    //and the velx transition (that was being multiplied with a factor of 0.925) reaches 0
        {
            CURRENT_STATE=MIDDLE;   //set the state to middle
        }
        velx = velx * 0.925f;
        Move(velx, vely);   //continue movement with the middle state
    }





}

void Cobra::Move(float x, float y)
{
    position.x = position.x + x;
    //These checks ensures that cobra doesnt leave the main game frame
    if(position.x<0)
    {
        position.x=0;
    }
    if(position.x>SCREEN_W - GetFrameWidth())
    {
        position.x = SCREEN_W - GetFrameWidth();
    }
    position.y = position.y + y;
    if(position.y > SCREEN_H + GetFrameHeight())
        SetAlive(false);
}

void Cobra::SetTarget(Object* object)
{
    target = object;
}

void Cobra::Draw(BITMAP* buffer, bool debug)
{
    //Cobra's draw function is called depending on current state of Cobra plane
    if(CURRENT_STATE == LEFT)
        masked_blit(image, buffer, 512, 0, position.x, position.y, frame_width,frame_height);
    else if(CURRENT_STATE == MIDDLE)
        masked_blit(image, buffer, 448, 0, position.x, position.y, frame_width,frame_height);
    else if(CURRENT_STATE == RIGHT)
        masked_blit(image, buffer, 384, 0, position.x, position.y, frame_width,frame_height);
    if(debug == true)
    {
        line(buffer, position.x,position.y, target->GetPosition().x,target->GetPosition().y, makecol(255, 0, 0));
        line(buffer, position.x,position.y, position.x+frame_width,position.y, makecol(255, 0, 0));
        line(buffer, position.x+frame_width,position.y, position.x+frame_width,position.y+frame_height, makecol(255, 0, 0));
        line(buffer, position.x,position.y+frame_height, position.x+frame_width,position.y+frame_height, makecol(255, 0, 0));
        line(buffer, position.x,position.y+frame_height, position.x,position.y, makecol(255, 0, 0));
    }
}

