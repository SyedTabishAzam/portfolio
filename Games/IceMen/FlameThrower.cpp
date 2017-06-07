#include "FlameThrower.h"
#include "sstream"

FlameThrower::FlameThrower(BITMAP* image,float x,float y,float width,float height)
{
    this->image = image;
    frame_height=height;
    frame_width=width;
    this->x = x;
    setAlive(true);
    this->y = y;
    walkstate = 0;
    type=11;
}

FlameThrower::~FlameThrower()
{
    cout<<"Flame thrower Destroyed"<<endl;
}

void FlameThrower::Draw(BITMAP* buffer)
{
    walkstate++;
    if(direction==RIGHT)
    {
        if(walkstate<30)
        {
            masked_blit(image, buffer, 0, 67, x,y, frame_width,frame_height);
        }
        else if(walkstate<60)
        {
            masked_blit(image, buffer, 50, 67, x,y, 48,41);
        }

    }
    else if(direction==LEFT)
    {
        if(walkstate<30)
        {
            masked_blit(image, buffer, 150, 67, x,y, frame_width,frame_height);
        }
        else if(walkstate<60)
        {
            masked_blit(image, buffer, 100, 67, x,y, 48,41);
        }
    }

    if(iceball == HOT)
    {

        masked_blit(image, buffer, 109, 118, x-1,y-24, 64,64);
    }
    else if(iceball == MELT)
    {

        masked_blit(image, buffer, 174, 118, x-1,y-24, 64,64 );
    }
    else if(iceball == WARM)
    {
        masked_blit(image, buffer, 248, 118, x-1,y-24, 64,64);

    }
    else if(iceball == COLD)
    {

        masked_blit(image, buffer, 318, 118, x-1,y-24, 64,64);
    }
    else if(iceball != NORMAL)
    {
        masked_blit(image, buffer, 394, 118, x-1,y-24, 64,64);
    }

    if(walkstate==59)
        walkstate=0;

}

void FlameThrower::ChangeState()
{
    if(GetHealth()==10000)
    {
        iceball = NORMAL;
    }
    if(GetHealth()<10000)
    {
        iceball = HOT;
    }
    if(GetHealth()<8000)
    {
        iceball=MELT;
    }
    if(GetHealth()<6000)
    {
        iceball=WARM;
    }
    if(GetHealth()<4000)
    {
        iceball=COLD;
    }
    if(GetHealth()<2000)
    {
        iceball=BALL;
        (health<0)?(health=0) : (health = health);
    }
}

void FlameThrower::Save(ofstream& f1)
{


    f1<<typeid(this).name()<<endl;
    f1<<typeid(this).name()<<"."<<this->x<<endl;
    f1<<typeid(this).name()<<"."<<this->y<<endl;
    f1<<typeid(this).name()<<"."<<this->health<<endl;
    f1<<typeid(this).name()<<"."<<this->type<<endl;
    f1<<"&"<<endl;
    cout<<this->health<<" here"<<endl;
}

void FlameThrower::Load(ifstream& f1)
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



}
