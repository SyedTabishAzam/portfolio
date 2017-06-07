#include "Sikh.h"

Sikh::Sikh(LTexture* sheet,LTexture* inventoryImage,TTF_Font *gFont,int pos,MOTION mr): Unit(sheet,inventoryImage,gFont,pos,mr)
{
    cout<<"Sikh Class Created"<<endl;


    this->width[IDLE] = 71.12;
    this->width[WALK] = 73.5;
    this->width[HURT] = 72;
    this->width[ATTACK] = 112;
    this->width[DEAD] = 107.5;

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
    stat.type=1;

    //Frame 0





}

Sikh::~Sikh()
{
    cout<<"Sikh class destroyed"<<endl;
}

void Sikh::Render(SDL_Renderer* gRenderer,int frame)
{

    int saveframe = frame;
    if(pauseframe)
    {


        frame=7;
    }

    if(direction!=1)
        cout<<direction<<" state is"<<endl;
    if (direction == RIGHT)
        (SpriteSheets+state)->Render( x + 30 - (width[state]/2)  , y - 30 , &spriteClips[state][ frame % FRAMES ], 0.0, NULL, SDL_FLIP_NONE, gRenderer );
    else
        (SpriteSheets+state)->Render( x  -30 + (width[state]/2), y -30, &spriteClips[state][ frame % FRAMES ], 0.0, NULL, SDL_FLIP_HORIZONTAL, gRenderer );


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



