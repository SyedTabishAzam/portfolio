#include"Plane.h"




Plane::Plane()
{
    frame_width = 64;
    frame_height = 64;
    health = 100;
}

Plane::~Plane()
{
    cout<<"Plane Deleted"<<endl;
}

Plane::Plane(BITMAP* image, int frame_width, int frame_height, Point position)
{
    this->frame_width = frame_width;
    this->frame_height = frame_height;
    this->image = image;
    this->position.x = position.x - frame_width/2;
    this->position.y = position.y - frame_height/2;
    health = 100;
    alive = true;
}

Plane::Plane(BITMAP* image, int frame_width, int frame_height, float x, float y)
{
    this->frame_width = frame_width;
    this->frame_height = frame_height;
    this->image = image;
    this->position.x = x - frame_width/2;
    this->position.y = y - frame_height/2;
    health = 100;
    alive = true;
}


Point Plane::GetPosition()
{
    return position;
}

int Plane::GetType()
{
    return type;
}

void Plane::SetPosition(Point* position)
{
    this->position.x = position->x - frame_width/2;
    this->position.y = position->y - frame_height/2;
}

void Plane::SetPosition(float x, float y)
{
    this->position.x = x - frame_width/2;
    this->position.y = y - frame_height/2;
}


void Plane::Move(float x, float y)
{
    position.x = position.x + x;
    position.y = position.y + y;
}

int Plane::GetFrameWidth()
{
    return frame_width;
}

int Plane::GetFrameHeight()
{
    return frame_height;
}

void Plane::SetAlive(bool alive)
{
    this->alive = alive;
}

bool Plane::Alive()
{
    return alive;
}

void Plane::SetHealth(int health)
{
    this->health = health;
}

int Plane::GetHealth()
{
    return health;
}

void Plane::TakeDamage(int damage)
{
    this->health = health - damage;
    if(health<=0)
        alive = false;
}


void Plane::SetVelocityX(float)
{

}
void Plane::SetVelocityY(float)
{

}
