#include "muslim.h"

muslim::muslim(LTexture* sheet,LTexture* inventoryImage,TTF_Font *gFont,int pos,MOTION mr): Unit(sheet,inventoryImage,gFont,pos,mr)
{
    cout<<"Muslim Class Created"<<endl;


    this->width[IDLE] = 38;
    this->width[WALK] = 60;
    this->width[ATTACK] = 60.373;
    this->width[HURT] = 48;
    this->width[DEAD] = 119;
    for(int j=0;j<5;j++)
    {

        height[j]=96;
        for(int i =0;i<FRAMES;i++)
        {
            spriteClips[j][ i ].x = i*width[j];
            spriteClips[j][ i ].y = 0;
            spriteClips[j][ i ].w = width[j];
            spriteClips[j][ i ].h = height[j];
        }
    }


    stat.speed = 5;
    stat.damage =30;
    stat.defense = 2;
    stat.health = 100;
    stat.type=2;







}

muslim::~muslim()
{
    cout<<"Muslim Class Destroyed"<<endl;
}

void muslim::Render(SDL_Renderer* gRenderer,int frame)
{

    int saveframe = frame;
    if(pauseframe)
    {
        frame=6;
    }


   if (direction == RIGHT)
        (SpriteSheets+state)->Render( x + 30 - (width[state]/2)  , y - 30 , &spriteClips[state][ frame % FRAMES ], 0.0, NULL, SDL_FLIP_NONE, gRenderer );
    else
        (SpriteSheets+state)->Render( x +30 - (width[state]/2), y -30, &spriteClips[state][ frame % FRAMES ], 0.0, NULL, SDL_FLIP_HORIZONTAL, gRenderer );


    if (((frame+1) % FRAMES) == 0)
    {
        if(state==DEAD)
        {

            pauseframe=true;
            if(saveframe==10)
            {
                //SetAlive(false);
                pauseframe=true;
            }
        }
        else if(state != DEAD )
        {
            state = IDLE;
        }

    }



}


