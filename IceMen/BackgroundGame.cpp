#include "BackgroundGame.h"

BackgroundGame::BackgroundGame(BITMAP* image,float x,float y)
{
    this->x = x;
    this->y = y;
    this->image = image;
}

BackgroundGame::~BackgroundGame()
{
    cout<<"Background deleted"<<endl;
}

void BackgroundGame::Draw(BITMAP* buffer)
{

    masked_blit(image,buffer,0,0,x,y,SCREEN_W,SCREEN_H);
}
