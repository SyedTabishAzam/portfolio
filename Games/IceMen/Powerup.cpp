#include "Powerup.h"

Powerup::Powerup(BITMAP* image,float x,float y,float width,float height)
{

    this->image = image;
    this->x = x;
    this->y=y;
    frame_width=width;
    frame_height=height;
    setAlive(true);
    type=15 + (rand()%3);
    damage = 0;
    duration = 0;


}

Powerup::~Powerup()
{
    cout<<"Powerup class destroyed"<<endl;
}



void Powerup::Draw(BITMAP* buffer)
{

    if(type==15)
        masked_blit(image, buffer, 282, 46, x,y, frame_width,frame_height);
    if(type==16)
        masked_blit(image, buffer, 298, 46, x,y, 15,19);
    if(type==17)
        masked_blit(image, buffer, 298, 67, x,y, 15,19);
}

void Powerup::Move()
{
    if(duration%1000==0)
    {
        cout<<duration<<endl;
    }
    if(duration==20000)
    {
        setAlive(false);
    }
    duration++;
}

void Powerup::Save(ofstream& f1)
{
    f1<<typeid(this).name()<<"."<<this->x<<endl;
    f1<<typeid(this).name()<<"."<<this->y<<endl;
    f1<<typeid(this).name()<<"."<<this->duration<<endl;
    f1<<typeid(this).name()<<"."<<this->type<<endl;
    f1<<"&"<<endl;
}
