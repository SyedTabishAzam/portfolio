#include"HealthBar.h"
#include <iostream>

using namespace std;
HealthBar::HealthBar(BITMAP* image, float x, float y)
{
    this->image=image;
    position.x=x;
    position.y=y;
    healthfactor=96;    //healthfactor i.e the size of healthbar
}


HealthBar::~HealthBar()
{
    cout<<"Healthbar Class Destroyed"<<endl;
}
void HealthBar::Move(float playerhp,int maxhealth)
{

    healthfactor = playerhp * (float(96)/float(maxhealth));
    //healthfactor is the aggrivate of player health on scale of 96 ( size of bar)
}

void HealthBar::Draw(BITMAP* buffer)
{
    //Draw the bar depending on players health percentage
    masked_blit(image,buffer,192,128,position.x,position.y,healthfactor,16);
    masked_blit(image,buffer,288,128,position.x,position.y,96,16);
    //Write health on location 0,0 of the screen
    Writer write(image,"health",true,0,0);
    write.Draw(buffer);

}



