#include "Unit.h"


Unit::Unit()
{

}

Unit::Unit(LTexture *sheet,LTexture* inventoryImage,TTF_Font *gFont,int pos,MOTION dr)
{
    direction = dr;
    invent = new Inventory(inventoryImage);
    SpriteSheets= sheet;


    pauseframe=false;
    this->gFont = gFont;
    float x = (pos % 11) * 60;
    float y = int(pos/11) *60;
    this->x = x;
    this->y = y;








    box.w= 60;
    box.h = 60;
    box.x = x;
    box.y = y;

    friction = 0.95f;
    speedx = 0;
    speedy = 0;
    alive  = true;

    animationComplete = true;





    this->pos = pos;
    stat.speed = 5;
    stat.damage =30;
    stat.defense = 2;
    this->focus = false;
    stat.health = 100;

    open.clear();




    extern LTexture itemImage[];
    Stats stats2;
    stats2.damage=100;
    stats2.speed=2;
    stats2.defense=50;

    stats2.type=MISC1;
    Item* item = new Item(&itemImage[BIGCLUB],"hammer",stats2,SMALL);
    stats2.type=HEAD;
    Item* item2 = new Item(&itemImage[HELMET],"hammer",stats2,SMALL);
    stats2.type=NONE;
    Item* item3 = new Item(&itemImage[BELT],"hammer",stats2,SMALL);


    invent->addItem(item);
    invent->addItem(item2);
    invent->addItem(item3);

//    ll.Push(item3);
//    ll.Push(item4);
//    ll.Push(item5);
//    ll.Push(item6);
//    ll.Push(item7);
//    ll.Push(item8);
}


Unit::~Unit()
{
    SpriteSheets = NULL;
}

void Unit::addItem(Item* it)
{
    invent->addItem(it);
}

Item* Unit::getItem()
{
    invent->getItem();
}

SDL_Rect Unit::getBox()
{
    return box;
}

void Unit::SetAlive(bool alive)
{
    this->alive = alive;
}

bool Unit::GetAlive()
{
    return alive;
}

void Unit::SetFocus(bool focus)
{
    this->focus = focus;
    if(focus==false)
    {
        open.clear();
        if(state!=DEAD && state!= ATTACK)
            state= IDLE;
    }
}

void Unit::SetState(int num)
{
    state = num;
}

bool Unit::GetFocus()
{
    return focus;
}
int Unit::getPosition()
{
    return pos;
}

void Unit::getHurt(float dam)
{
    stat.health = stat.health - dam;

    if(state!=DEAD)
        state=HURT;

    if(stat.health<0)
    {
        state=DEAD;
        stat.health=0;
    }
    animationComplete=false;
}

int Unit::getDamage()
{
    state=ATTACK;
    cout<<"Here"<<endl;
    return stat.damage;
}
int Unit::getSpeed()
{
    return stat.speed;
}

int Unit::getType()
{
    return stat.type;
}
void Unit::Move(int dest)
{


    if(focus==true)
    {


        int destx = (dest % 11) * 60;
        int desty = int(dest/11) *60;

        int sourcex = x;
        int sourcey = y;

        int midDestx = ((destx) + (destx+60)) /2;
        int midDesty = ((desty) + (desty+60)) /2;

        int midSourcex = ((sourcex) + (sourcex+60)) /2;
        int midSourcey = ((sourcey) + (sourcey+60)) /2;
        bool moving =false;




            if (midSourcex<midDestx)
            {
                x = x + 2;
                direction = RIGHT;
                moving = true;
            }
            if (midSourcey<midDesty)
            {
                y = y + 2;
                moving = true;
            }
            if (midSourcex>midDestx)
            {
                x = x - 2;
                direction = LEFT;
                moving = true;
            }
            if (midSourcey>midDesty)
            {
                y = y - 2;
                moving = true;
            }
            if(state!=DEAD)
                state=WALK;
            if(!moving)
            {

                pos = dest;

            }

            box.x = x;
            box.y=y;

    }

}

void Unit::Move()
{
     speedx = speedx * friction;
     speedy = speedy * friction;

     x = x + speedx;
     y = y + speedy;
}

float Unit::getX()
{
    return x;
}


float Unit::getY()
{
    return y;
}


void Unit::showStats( SDL_Renderer* gRenderer)
{
    invent->showStats(gRenderer);
}

vector<int> Unit::showReachable()
{
    //calls a function to be global

    if(open.size()==0)
    {


        extern vector<int> neighbors(int);

        //declare arrays for dynamic programming
        //Open arrays are yet to be explored

        DoubleLinkedList<int> open1;


        //closed are the ones already explored


        //pushes the current position of unit to the array
        open1.Push(pos);


        //it points to the begining of opening array


        int ct=0;


        //loop till end of open array
        while  (open1.GetLength() != ((pow(4,stat.speed+1)-1)/(4-1)))
        {

            int current = open1.ElementAt(ct);

            //if the position for which neighbours are to be found is already explored, move next
            vector<int> neigh;
            neigh = neighbors(current);
            vector<int>::iterator nei;



            //for all the neighbours found
            for(nei = neigh.begin();nei!=neigh.end();nei++)
            {
                    //if all the neighbours arent added to open list, add them
                    int item = *nei;


                    open1.Push(item);

            }

            for(int j=0;j<(4-neigh.size());j++)
            {
                open1.Push(current);
            }
                //increase open size by adding dummy node that is position. This is done to ensure that algorith halts





            //explored node pushed to close



            //increase the open iterator to look up for next node


            ct++;


        }

        while (open1.isEmpty()==false)
        {
            open.push_back(open1.Pop());
        }


    }

    return open;
}

int Unit::GetState()
{
    return state;
}

void Unit::SetMotion(int mt)
{
    direction = mt;
}

int Unit::GetMotion()
{
    return direction;
}
vector<int> Unit::showEssential( SDL_Renderer* gRenderer)
{

    showStats(gRenderer);

    return showReachable();

}

void Unit::showInventory( SDL_Renderer* gRenderer)
{



    invent->Render(gRenderer);
}

void Unit::drawText(string text,int x,int y, SDL_Renderer* gRenderer)
{

		//Render text
    SDL_Color textColor = { 0, 0, 0 };

    if( !gTextTexture.loadFromRenderedText( text,gFont, textColor, gRenderer ) )
    {
        printf( "Failed to render text texture!\n" );

    }
    else
    {
        gTextTexture.Render( x, y, NULL, 0.0, NULL, SDL_FLIP_NONE, gRenderer );

    }

}

void Unit::Render(SDL_Renderer* gRenderer,int frame)
{



    SDL_RenderDrawLine(gRenderer,x,y,x+60,y);
    SDL_RenderDrawLine(gRenderer,x+60,y,x+60,y+60);
    SDL_RenderDrawLine(gRenderer,x,y,x,y+60);
    SDL_RenderDrawLine(gRenderer,x,y+60,x+60,y+60);



}


