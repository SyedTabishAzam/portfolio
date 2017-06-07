#include "SnowMan.h"

SnowMan::SnowMan(BITMAP* image,float x,float y,float width,float height)
{
    this->image = image;
    frame_width = width;
    frame_height = height;
    ChangeAttrib(1,1,2);
    health = 3;
    damage=0;
    walkstate = 0;
    triggered = false;
    setAlive(true);
    this->x = x;
    this->y = y;
    type = 1;
    gamespeed=0;
    chance = 0;
}

SnowMan::~SnowMan()
{
    cout<<"SnowMan Deleted"<<endl;
}

void SnowMan::Draw(BITMAP* buffer)
{
    if (state==RIGHT)
    {
        if(walkstate<75)
        {
            masked_blit(image, buffer, 42, 12, x,y, 47,56);
            walkstate++;
        }
        else if(walkstate <150)
        {

            masked_blit(image, buffer, 88, 12, x,y, 43,56);
            walkstate++;
        }
        if(walkstate == 150)
        {
            walkstate = 0;
        }
    }
    if (state==LEFT)
    {
        if(walkstate<75)
        {
            masked_blit(image, buffer, 173, 12, x,y, 47,56);
            walkstate++;
        }
        else if(walkstate <150)
        {

            masked_blit(image, buffer, 131, 12, x,y, 43,56);
            walkstate++;
        }
        if(walkstate == 150)
        {
            walkstate = 0;
        }
    }
    if (state==JUMP)
    {
        if(facingstate==LEFT)
            masked_blit(image, buffer, 219, 12, x,y, 42,56);
        else if(facingstate==RIGHT)
            masked_blit(image, buffer, 0, 12, x,y, 42,56);
    }
    if(state==FREE)
    {
        if(facingstate==LEFT)
            masked_blit(image, buffer, 219, 12, x,y, 42,56);
        else if(facingstate==RIGHT)
            masked_blit(image, buffer, 0, 12, x,y, 42,56);
    }



}

void SnowMan::Move()
{


    if(triggered==true)
    {
        gamespeed++;


        if(gamespeed<350 && gamespeed > 0)
        {
            if(chance>=4)
            {
                float tempy = y;
                ChangePosition(x,y-1);
                if(y==tempy)
                {
                    gamespeed=350;
                }
                chance = 0;
            }

        }
        else
        {

            if(!onGround())
            {
                if(chance>=4)
                {
                    ChangePosition(x,y+1);
                    chance = 0;
                }

            }
            else
            {
                triggered=false;
                gamespeed = 0;
            }
        }
        chance++;

    }
    else
    {
        ApplyGravity();
    }
}



int SnowMan::getSpeed()
{
    return speed;
}

void SnowMan::setSpeed(int spd)
{
    speed = spd;
}

void SnowMan::ChangeState(direction d,int gamespeed)
{

    state = d;
    if(state!=JUMP && state != FREE)
        facingstate = d;
    switch(d)
    {
    case RIGHT:
        ChangePosition(x + getSpeed(),y);
        break;
    case LEFT:
        ChangePosition(x - getSpeed(),y);
        break;
    case JUMP:
        if(onGround())
        {
            triggered = true;
        }
        break;
    case FREE:
        break;
    }
}

int SnowMan::GetState()
{
    return state;
}

void SnowMan::UsePup(int pup)
{
    //if yellow powerup is picked, call method ChangeBullet, else call method CreateArmour
    cout<<pup<<" this is pup"<<endl;
    if(pup==YELLOW)
    {
        cout<<"powerup1"<<endl;
        ChangeAttrib(bullettype,2,speed);
    }
    else if(pup==RED)
    {
        cout<<"powerup2"<<endl;
        ChangeAttrib(bullettype,bulletlength,4);
    }
    else if(pup==BLUE)
    {

        cout<<"powerup3"<<endl;
        ChangeAttrib(3,bulletlength,speed);
    }

}

void SnowMan::ChangeAttrib(int btype,int blength,int spd)
{   //Method called when  powerup picked
   bullettype = btype;
   speed = spd;
   bulletlength = blength;
}

Object* SnowMan::Fire()
{

    Bullet* bullet = new Bullet(this->image ,facingstate,bullettype,bulletlength ,this->x+36/2, this->y+10,15,22);
    return bullet;
}

void SnowMan::TakeDamage(int dam)
{
    health = health - dam;
    if(health==0)
    {
        setAlive(false);
    }
    ResetPosition();

}


void SnowMan::ResetPosition()
{
    ChangeAttrib(1,1,2);
    ChangePosition(450,SCREEN_H-64);
}

void SnowMan::Save(ofstream& f1)
{
    f1<<typeid(this).name()<<endl;
    f1<<typeid(this).name()<<"."<<this->x<<endl;
    f1<<typeid(this).name()<<"."<<this->y<<endl;
    f1<<typeid(this).name()<<"."<<this->health<<endl;
    f1<<typeid(this).name()<<"."<<this->type<<endl;
    f1<<typeid(this).name()<<"."<<this->speed<<endl;
    f1<<typeid(this).name()<<"."<<this->bullettype<<endl;
    f1<<typeid(this).name()<<"."<<this->bulletlength<<endl;
    f1<<"&"<<endl;

}

void SnowMan::Load(ifstream& f1)
{
    string line,value;
    float helper;
    stringstream pars;

    getline(f1,line);
    value = line.substr(line.find(".")+1);
    pars<<value;
    pars>>this->x;
    pars.clear();


    getline(f1,line);
    value = line.substr(line.find(".")+1);
    pars<<value;
    pars>>this->y;
    pars.clear();

    getline(f1,line);
    value = line.substr(line.find(".")+1);
    pars<<value;
    pars>>this->health;
    pars.clear();

    getline(f1,line);
    value = line.substr(line.find(".")+1);
    pars<<value;
    pars>>this->type;
    pars.clear();

    getline(f1,line);
    value = line.substr(line.find(".")+1);
    pars<<value;
    pars>>this->speed;
    pars.clear();

    getline(f1,line);
    value = line.substr(line.find(".")+1);
    pars<<value;
    pars>>this->bulletlength;
    pars.clear();

    getline(f1,line);
    value = line.substr(line.find(".")+1);
    pars<<value;
    pars>>this->bullettype;
    pars.clear();
    cout<<"yes"<<endl;


}
