#include "Hurdles.h"

Hurdles::Hurdles(BITMAP* image,float x,float y,float width,float height)
{
    this->image = image;
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    type = 30;
    frame_width = width;
    frame_height= height;
    setAlive(true);
}

Hurdles::~Hurdles()
{
    cout<<"Hurdles Class Destroyed"<<endl;
}

void Hurdles::Draw(BITMAP* buffer)
{


    masked_blit(image,buffer,0,0,x,y,width,height);
    line(buffer, x,y, x+frame_width,y, makecol(255, 0, 0));
    line(buffer, x+frame_width,y, x+frame_width,y+frame_height, makecol(255, 0, 0));
    line(buffer, x,y+frame_height, x+frame_width,y+frame_height, makecol(255, 0, 0));
    line(buffer, x,y+frame_height, x,y, makecol(255, 0, 0));
}

void Hurdles::Move()
{

}

void Hurdles::Save(ofstream& f1)
{
    f1<<typeid(this).name()<<endl;
    f1<<typeid(this).name()<<"."<<this->x<<endl;
    f1<<typeid(this).name()<<"."<<this->y<<endl;
    f1<<typeid(this).name()<<"."<<this->width<<endl;
    f1<<typeid(this).name()<<"."<<this->height<<endl;
    f1<<"&"<<endl;
}

void Hurdles::Load(ifstream& f1)
{
    string line,value;
    float helper;
    stringstream pars;

    getline(f1,line);
    value = line.substr(line.find(".")+1);
    cout<<value<<endl;
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
    pars>>width;
    pars.clear();


    getline(f1,line);
    value = line.substr(line.find(".")+1);
    pars<<value;
    pars>>height;
    pars.clear();

    frame_width = width;
    frame_height= height;

}
