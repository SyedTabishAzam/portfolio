#include "Score.h"


Score::Score(BITMAP* img,int posx,int posy)
{
    //initializes image and position of the dying enemy
    image = img;
    positionx = posx;
    positiony = posy;
    sc=0;
}

Score::~Score()
{
    cout<<"Score class Destroyed"<<endl;
}

void Score::AddGlobal(int checker)
{

    //extern int g_c is the global counter, that is forward declared here
    extern int g_c;
    if(checker==14)     //if the type of object was 14 (recieved when initializing,) that indicates it was cobra
    {

        g_c = g_c + 10; //append 10 points to global variable
    }
    else if(checker ==13)   //if type was viper,
    {

        g_c = g_c + 5;  //append 5 points to the global
    }
}

void Score::Determine(int checker)
{
    if(checker==14)     //this function determines the local scope of score, for drawing purpose
    {
        sc = 10;        //10 is added to sc variable if cobra was killed
    }
    else if(checker==13)
    {
        sc = 5;     //5 is added to sc variable if cobra was killed
    }
}

void Score::Draw(BITMAP* buffer)
{

    if(sc==5)
    {
        masked_blit(image,buffer,160,400,positionx,positiony,32,32);    //if viper is killed, draw number 5 on screen
    }
    else if(sc==10)
    {

        masked_blit(image,buffer,32,400,positionx,positiony,32,32);     //if cobra was killed, draw number 10
        masked_blit(image,buffer,0,400,positionx+16,positiony,32,32);
    }


}
