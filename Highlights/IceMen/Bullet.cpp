#include "Bullet.h"

Bullet::Bullet(BITMAP* image,direction state,int type,int length, float x , float y,float width,float height )
{
    frame_height = height;
    frame_width = width;
    this->image = image;
    this->x = x;
    this->state=state;
    this->y = y;
    this->length=length;
    this->type=type;
    setAlive(true);
    damage = 2000;
    health = 1;
    alivevar = 0;
}

Bullet::~Bullet()
{
    cout<<"Bullet Destroyed"<<endl;
}

void Bullet::Move()
{
    if(type==2)
    {
        damage = 2000;
    }
    else if(type==3)
    {
        damage = 4000;
    }
    float factor;

    (length==1)?(factor=0.4):(factor=0.8);
    if(!onGround())
    {
        if(state==LEFT)
        {
            x=x-factor;
        }
        else
        {
            x=x+factor;
        }
        if(alivevar<100)
        {
            y = y - 0.1;
        }
        else
        {
            y = y + 0.2;
        }


    }


}

void Bullet::Draw(BITMAP* buffer)
{
    if(state==LEFT)
        masked_blit(image, buffer, 282, 12, x,y, frame_width,frame_height);
    else
        masked_blit(image, buffer, 295, 12, x,y, frame_width,frame_height);
}

void Bullet::TakeDamage(int dam)
{
    health = health - dam;
    if(health<=0)
        setAlive(false);
}

void Bullet::Save(ofstream& f1)
{
    cout<<"Sa"<<endl;
    f1<<typeid(this).name()<<"."<<this->x<<endl;
    f1<<typeid(this).name()<<"."<<this->y<<endl;
    f1<<typeid(this).name()<<"."<<this->health<<endl;
    f1<<typeid(this).name()<<"."<<this->type<<endl;
    f1<<typeid(this).name()<<"."<<this->state<<endl;
    f1<<typeid(this).name()<<"."<<this->type<<endl;
    f1<<typeid(this).name()<<"."<<this->length<<endl;
    f1<<"&"<<endl;

}
