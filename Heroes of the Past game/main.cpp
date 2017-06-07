#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include "Sikh.h"
#include "muslim.h"
#include "Node.h"
#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <bitset>
#include "LTexture.h"
#include <math.h>
#include <iterator>
#include "Queue.h"
#include "Tile.h"
#include "Unit.h"
#include "Enemy.h"
#include <map>
#include <vector>
#include <fstream>
#include <iostream>
#include <algorithm>
//Pre defined screen width and height
const int SCREEN_WIDTH = 800 ;
const int SCREEN_HEIGHT = 556;


bool init();
vector<int> astar(int,int);
bool loadMedia();
vector<int> neighbors(int);
void close();
float hcost(int dest,int start);
SDL_Window* gWindow = NULL;

SDL_Renderer* gRenderer = NULL;

TTF_Font *gFont = NULL;
LTexture MuslimSheet[5];
LTexture SikhSheet[5];
LTexture itemImage[20];

LTexture sikhImage;
LTexture cursImg;
LTexture tImage;
LTexture invIcon;
LTexture terrain;
LTexture storyPage;
LTexture bookIcon;
LTexture hurdle;
LTexture inventoryTexture;
LTexture ms1;
bool init();
bool loadMedia();
void close();

int AI(DoubleLinkedList<Unit*>&,Unit*&,Unit*&);


int main(int argc, char* args[])
{
	//Start up SDL and create window
	if( !init() )
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{
		//Load media
		if( !loadMedia() )
		{
			printf( "Failed to load media!\n" );
		}
		else
		{

			bool quit = false;                      //Main loop flag

			SDL_Event e;                            //Event handler

			long int frame = 0;                     //Current animation frame

			/* initialize random seed: */
            srand (time(NULL));

            /* generate secret number between 1 and 10: */
            int random = 0;
            DoubleLinkedList<Unit*> li;
			Unit* Muslim1 = new muslim(MuslimSheet,&inventoryTexture,gFont, 11,RIGHT);
			Unit* Muslim2 = new muslim(MuslimSheet,&inventoryTexture,gFont, 33,RIGHT);
			Unit* Muslim3 = new muslim(MuslimSheet,&inventoryTexture,gFont, 55,RIGHT);

			Unit* sikh1 = new Sikh(SikhSheet,&inventoryTexture,gFont, 21,LEFT);
            Unit* sikh2 = new Sikh(SikhSheet,&inventoryTexture,gFont, 43,LEFT);
            Unit* sikh3 = new Sikh(SikhSheet,&inventoryTexture,gFont, 65,LEFT);


			li.Push(Muslim1);
			li.Push(Muslim2);
			li.Push(Muslim3);

            li.Push(sikh1);
            li.Push(sikh2);
            li.Push(sikh3);

            Tile* tile[100];
            char fchar;
            ifstream file1("map.txt",ios::in);
            Unit* sel;
            for (int i =0;i<100;i++)
            {

                int row = int(i/11);
                file1.seekg((i*2)+row,ios::beg);
                file1.get(fchar);
                string s(1,fchar);
                stringstream ss;
                ss<<s;
                int x = 0;
                ss >> x;
                tile[i]= new Tile(&tImage,x,i);

            }

            file1.close();

            int save = 0;
            vector<int> route;
            vector<int> accessible;
            vector<int>::iterator it;
            vector<int>::iterator xt;

            bool travel = false;
            bool routeFound = false;
            bool calculate = false;
            bool showInv = false;
            int next;
            int start;
            int mousePosX, mousePosY;
            mousePosX = 0;
            mousePosY = 0;
            bool turn;
            turn = 1;
            bool selected = false;
            bool story[2] = {false};
            bool showStory[2]={false};
            bool firstTime = true;
            int controller = 0;
            Unit* LtoBeAttacked;
            bool attackAtRouteEnd = false;
            SDL_ShowCursor(0);
			while( !quit )                          //While application is running
			{

			    if(frame%2 == 0)
                {
                    random = rand() % SCREEN_WIDTH;
                }
				while( SDL_PollEvent( &e ) != 0 )   //Handle events on queue
				{
                    if(e.type== SDL_MOUSEMOTION)
                        SDL_GetMouseState( &mousePosX, &mousePosY );
                    //User requests quit
					if( e.type == SDL_QUIT )
					{
						quit = true;
					}
					const Uint8* currentKeyStates = SDL_GetKeyboardState( NULL );
                    if( e.type == SDL_MOUSEBUTTONDOWN )
                    {
                        if( e.button.button == SDL_BUTTON_LEFT )
                        {
                            int x = e.button.x;
                            int y = e.button.y;

                            int pp = int(x/60) + (int(y/60)*11);
                        if (turn == 1)
                        {


                                if(selected && !routeFound && !showInv && !showStory[0] && !showStory[1]&& tile[pp]->getOccupied()==false)
                                {
                                    tile[sel->getPosition()]->setOccupied(false);
                                    save = pp;

                                    travel = true;
                                    calculate=true;
                                }
                                else if(selected && !showInv && !showStory[0] && !showStory[1] && tile[pp]->getOccupied()==true && pp!=sel->getPosition() )
                                {
                                    Unit* temp = li.getUnitByPos(pp);
                                    if((temp->getType()!=sel->getType()) && temp->GetState()!=DEAD &&hcost(temp->getPosition(),sel->getPosition())<2)
                                    {
                                        frame = 0;
                                        cout<<"Ahh, Damage22"<<sel->getDamage()<<endl;
                                        temp->getHurt(sel->getDamage());
                                        if(sel->getX()<temp->getX())
                                        {
                                            sel->SetMotion(RIGHT);
                                            temp->SetMotion(LEFT);
                                        }
                                        else
                                        {
                                            sel->SetMotion(LEFT);
                                            temp->SetMotion(RIGHT);
                                        }
                                        if(temp->GetState()==DEAD)
                                        {
                                            tile[pp]->setOccupied(false);
                                            story[0]=true;
                                        }

                                    }

                                }
                                if(showInv)
                                {


                                    if(x>260 && x<280 && y>40 && y<50)
                                    {
                                            showInv = false;
                                    }

                                }
                                if(showStory[0]==true || showStory[1]==true)
                                {
                                    if(x>353 && x<378 && y>0 && y<26)
                                    {
                                            showStory[0]=false;
                                            showStory[1]=false;

                                    }

                                }



                        }
                        }
                        if( e.button.button == SDL_BUTTON_RIGHT )
                        {
                            int x = e.button.x;
                            int y = e.button.y;
                            int pp = int(x/60) + (int(y/60)*11);
                            if(turn==1)
                            {



                                if(x>0 && x<64 && y>0 && y<64)
                                {
                                        showStory[0]=true;



                                }
                                else if(!showInv && !showStory[0] && !showStory[1]&& !routeFound && !selected && !attackAtRouteEnd)
                                {

                                    sel = li.getUnitByPos(pp);

                                    if (sel!=NULL && sel->GetState()!=DEAD && sel->getType() ==1  && sel->GetState()!=DEAD)
                                    {
                                        selected=true;

                                        sel->SetFocus(true);

                                    }

                                }
                                if (selected)
                                {
                                    if(x>0 && x<50 && y > 200 && y <248)
                                    {
                                        showInv = true;
                                    }


                                }

                            }
                        }

                    }
                    else if ( e.type == SDL_MOUSEBUTTONUP )
                    {

                    }

				}

				if(turn==0)
                {

                    if(firstTime==true)
                    {
                        cout<<"coming here"<<endl;
                        Unit* toBeAttacked = NULL;
                        save = AI(li,sel,toBeAttacked);


                        if(toBeAttacked!=NULL)
                        {


                            attackAtRouteEnd = true;
                            LtoBeAttacked = toBeAttacked;

                        }
                        firstTime=false;
                        cout<<"jee"<<endl;
                        sel->SetFocus(true);
                        tile[sel->getPosition()]->setOccupied(false);
                        travel = true;
                        calculate=true;
                    }


                }


                if (calculate)
                {
                    start = sel->getPosition();

                }

                if (travel)
                {
                        cout<<start<<" "<<save<<endl;
                        route = astar(start,save);
                        if((route.size()>1) && (route.size()<=sel->getSpeed()+1))
                        {
                            xt = route.end() - 1;
                            next = *(xt-1);
                            if(sel->getX()<tile[save]->getBox().x)
                            {
                                sel->SetMotion(RIGHT);
                            }
                            if(sel->getX()>tile[save]->getBox().x)
                            {
                                sel->SetMotion(LEFT);
                            }
                            routeFound = true;

                            sel->SetFocus(true);
                        }
                        else if(start==save)
                        {
                            next = save;
                            routeFound = true;

                          //  sel->SetFocus(true);
                        }
                        else
                        {
                            routeFound = false;
                            route.clear();
                        }

                        travel = false;
                }




				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );    //Clear screen
				SDL_RenderClear( gRenderer );
                terrain.Render(0,0,NULL,0.0,NULL,SDL_FLIP_NONE,gRenderer);
				for (int i =0;i<100;i++)
                {
                    tile[i]->Render(gRenderer);
                    tile[i]->clicked(false);
                    tile[i]->setReachable(false);
                }


                li.RenderAll(gRenderer,frame);




                if(selected==true)
                {


                    invIcon.Render(0,200,NULL,0.0,NULL,SDL_FLIP_NONE,gRenderer);

                    accessible = sel->showEssential(gRenderer);

                    for(it=accessible.begin();it!=accessible.end();it++)
                    {
                        tile[*it]->setReachable(true);

                    }


                    if(showInv)
                    {
                        SDL_SetRenderDrawColor( gRenderer, 166, 166, 166, 128 );
                        SDL_RenderFillRect( gRenderer,NULL);
                        SDL_SetRenderDrawBlendMode(gRenderer,SDL_BLENDMODE_ADD);
                        sel->showInventory(gRenderer);
                    }
                    else
                    {
                        SDL_SetRenderDrawBlendMode(gRenderer,SDL_BLENDMODE_NONE);
                    }



                }

                if(story[0]==true || story[1]==true)
                {
                    bookIcon.Render(0,0,NULL,0.0,NULL,SDL_FLIP_NONE,gRenderer);
                    if(showStory[0]==true)
                    {
                        storyPage.Render(0,0,NULL,0.0,NULL,SDL_FLIP_NONE,gRenderer);
                        ms1.Render(0,0,NULL,0.0,NULL,SDL_FLIP_NONE,gRenderer);

                    }
                }

                for(it=route.begin();it!=route.end();it++)
                {

                   tile[*it]->clicked(true);

                }

                if(controller==5)
                {
                    controller=0;
                    ++frame;
                }
                controller++;

                if(routeFound && sel->GetFocus()==true)
                {






                    if (start==next)
                    {

                        if(start==save)
                        {
                            if(attackAtRouteEnd)
                            {
                                frame = 0;
                                cout<<"Ahh, Damageahah"<<LtoBeAttacked->getDamage()<<" "<<frame<<endl;
                                LtoBeAttacked->getHurt(sel->getDamage());
                                if(sel->getX()<LtoBeAttacked->getX())
                                {
                                    sel->SetMotion(RIGHT);
                                    LtoBeAttacked->SetMotion(LEFT);
                                }
                                else
                                {
                                    sel->SetMotion(LEFT);
                                    LtoBeAttacked->SetMotion(RIGHT);
                                }
                                if(LtoBeAttacked->GetState()==DEAD)
                                {
                                    tile[LtoBeAttacked->getPosition()]->setOccupied(false);
                                    story[0]=true;
                                }
                                attackAtRouteEnd = false;
                            }
                            else
                            {

                            routeFound=false;
                            //if(sel->getType()==2 && sel->GetState() != ATTACK)
                            sel->SetFocus(false);
                            tile[sel->getPosition()]->setOccupied(true);


                            turn = !turn;
                            if(turn==0)
                                firstTime=true;
                            selected=false;

                            }

                        }
                        else
                        {

                            xt = xt - 1;
                            next = *xt;

                        }

                    }
                    else
                    {

                        sel->Move(next);
                    }
                }
                else
                {

                    calculate=false;
                    route.clear();
                }




                cursImg.Render(mousePosX,mousePosY,NULL,0.0,NULL,SDL_FLIP_NONE,gRenderer);
				SDL_RenderPresent( gRenderer );     //Update screen

				                            //Go to next frame

            li.CleanAll();
			}

		}
	}

	//Free resources and close SDL
	close();
    char x;
    getchar();
	return 0;
}

vector<int> astar(int pos,int destination)
{


    map<Data,int> openArr;
    map<Data,int> close;
    map<Data,int>::iterator openIt;
    map<Data,int>::iterator closeIt;

    Data n;
    n.pos = pos;
    n.cost = hcost(pos,destination);
    int Starthcost = hcost(pos,destination);
    openArr.insert(std::pair<Data,int>(n,Starthcost));


    vector<int> sol;
    map<Data,int>::iterator currentNode;


    while (!openArr.empty())
    {


        int lowest = 99999;
        map<Data,int>::iterator openIt;
        for(openIt=openArr.begin();openIt!=openArr.end();openIt++)
        {

            if(((openIt->first).cost)<lowest)
            {

                lowest = (openIt->first).cost;
                currentNode = openIt;
            }
        }

        //Current Node is element of map.
        int level = currentNode->second;
        openIt=openArr.begin();


        openArr.erase(currentNode);

        close.insert(std::pair<Data,int>(currentNode->first,level));



        int checkVal;
        checkVal=(currentNode->first).pos;
        int starter = level;
        if ((currentNode->first).pos == destination)
        {

            close.insert(std::pair<Data,int>(currentNode->first,level));
            map<Data,int>::iterator closeIt;


            sol.push_back((currentNode->first).pos);




            map<Data,int>::iterator checkIt;
            while(checkVal != pos)
            {

                int level = starter;
                map<Data,int> check;

                //for every element of close

                for(closeIt=close.begin();closeIt!=close.end();closeIt++)
                {
                    //select elements that have level - 1
                    if ((closeIt->second)==(level-1))
                    {
                        //insert it into check with their level
                        check.insert(std::pair<Data,int>(closeIt->first,level-1));


                    }
                }





                //find neighbors of parent


                //for every element in checkit, every element that has level - 1
                checkIt = check.begin();

                for(checkIt=check.begin();checkIt!=check.end();checkIt++)
                {


                    vector<int>::iterator xit;
//
                   // bool connected = ((find(neigh.begin(),neigh.end(),(checkIt->first).pos)) != neigh.end());
//                  //check if the element is connected to the parent

                    vector<int> neigh = neighbors((checkIt->first).pos);
                    for(xit=neigh.begin();xit!=neigh.end();xit++)
                    {

                        if(checkVal==(*xit))
                        {
                            //if it is, it is the new parent
                            checkVal = (checkIt->first).pos;
                            starter = checkIt->second;

                            sol.push_back(checkVal);



                            break;
                        }
                    }






                }
//

            }


            return sol;
        }


        vector<int> neigh = neighbors((currentNode->first).pos);


        vector<int>::iterator it;


        for(it=neigh.begin();it!=neigh.end();it++)
        {

            int hn=0;
            int cost = (currentNode->first).cost - hcost((currentNode->first).pos,destination) + 1;

            bool existOpen=false;
            bool existClosed=false;
            Data q;
            Data v;

            for(openIt=openArr.begin();openIt!=openArr.end();openIt++)
            {


                if(((openIt->first).pos)==(*it))
                {
                    existOpen=true;
                    q = openIt->first;

                    break;
                }
            }

            for(closeIt=close.begin();closeIt!=close.end();closeIt++)
            {


                if(((closeIt->first).pos)==(*it))
                {
                    existClosed=true;
                    v = closeIt->first;

                    break;
                }
            }
            if(existOpen)
            {


                int partA= q.cost - hcost(q.pos,destination);
                if (partA<=cost)
                {

                    continue;
                }

            }
            else if(existClosed)
            {


                int partA= v.cost - hcost(v.pos,destination);

                if (partA<=cost)
                {

                    continue;
                }

                close.erase(v);

                openArr.insert(std::pair<Data,int>(v,level));

            }
            else
            {

                hn = hcost(destination,(*it));

            }

                Data ren;
                ren.pos = (*it);
                ren.cost = hn+cost;

                openArr.insert(std::pair<Data,int>(ren,level+1));


        }


    }

    if((currentNode->first).pos != destination)
    {
        sol.clear();
        sol.push_back(pos);
    }
    return sol;

}

float hcost(int dest,int start)
{

    if(dest<start)
    {
        return hcost(start,dest);
    }
    int parta = dest - start;

    int partb = int(parta/11);

    int partheight = dest - (partb*11);

    if (int(partheight/11)>int(start/11))
    {
        partb = partb + 1;

        partheight = dest - (partb*11);

    }

    int partlength = abs(partheight - start);

    float hs = sqrt(pow(partb,2) + pow(partlength,2));

    return hs;
}

vector<int> neighbors(int current)
{

    vector<int> output;
    char chChar;
    ifstream file("map.txt",ios::in);



    for(int loop=0;loop<4;loop++)
    {
        int n1;
        if(loop==0)
        {
            n1=current-1;

        }
        if(loop==1)
        {
            n1=current+1;
        }
        if(loop==2)
        {
            n1=current-11;
        }
        if(loop==3)
        {
            n1=current+11;
        }
//         if(loop==4)
//        {
//            n1=current-12;
//
//        }
//        if(loop==5)
//        {
//            n1=current+12;
//        }
//        if(loop==6)
//        {
//            n1=current-10;
//        }
//        if(loop==7)
//        {
//            n1=current+10;
//        }
        int row = int(abs(n1)/11);
        file.seekg((abs(n1)*2)+row,ios::beg);
        file.get(chChar);
        string s(1,chChar);

        if(s=="1")
        {
            output.push_back(n1);
        }
    }

    vector<int>::iterator it;
    vector<int> real;
    for(it=output.begin();it!=output.end();it++)
    {
        int number = *it;

        if((number>=0) && (number <=86))
        {
            if(number==(current+1) && (number % 11) != 0)
            {
            real.push_back(number);
            }
            if(number==(current-1) && (number % 11) != 10)
            {
               real.push_back(number);
            }
            if((number==(current+11)) || (number==(current-11)))
            {
                real.push_back(number);
            }
//            if((number==(current+10)) || (number==(current-10)))
//            {
//                real.push_back(number);
//            }
//            if((number==(current+12)) || (number==(current-12)))
//            {
//                real.push_back(number);
//            }
        }


    }


    file.close();

    return real;

}



int AI(DoubleLinkedList<Unit*>& li,Unit*& sel,Unit*& toBeAttacked)
{

    int lengthOfLi = li.GetLength();
    int x = 0;
    Unit* unit;
    bool enemyFound = false;

    int countEnemy = 0;
    int countPlayer = 0;

    /*-----------COUNTING TOTAL NUMBER OF ENEMIES AND ALLIES-------------------*/
    while(x<lengthOfLi)
    {
        unit = li.ElementAt(x);
        if(unit->getType()==1  && unit->GetState()!=DEAD)
        {
            countPlayer++;
        }
        else if(unit->getType()==2  && unit->GetState()!=DEAD)
        {
            countEnemy++;
        }
        x++;
    }


    /*-----------Randomly choosing a player (muslim)-------------------*/
    x = 0;
    float probability = rand()%10;
    Unit* player;
    while(x<lengthOfLi)
    {
        player = li.ElementAt(x);
        if(player->getType()==1  && player->GetState()!=DEAD)
        {
            countPlayer--;
            if(countPlayer==0)
            {
                break;
            }
            if(probability<5)
            {
                probability = probability * 2;
            }
            else
            {
                break;
            }
        }
        x++;
    }

    /*-----------Choosing an emeny unit based on lowest heuristic score -------------------*/
    x=0;
    Unit* enem;
    int miniMum = 900;
    while(x<lengthOfLi)
    {
        Unit* sikh = li.ElementAt(x);
        if(sikh->getType()==2 && sikh->GetState()!=DEAD)
        {
            int hCost = hcost(player->getPosition(),sikh->getPosition());
            if(hCost<miniMum)
            {
                miniMum = hCost;
                enem = sikh;
            }

        }
        x++;
    }

    /*-----------------------Find the closest location possible (to the opponent)-----------------------*/

     vector<int> vicinity = enem->showReachable();
     vector<int>::iterator itx;
    int closest2 = 999;
    int closestPossible = 0;
    int opponent = 0;
    for(itx=vicinity.begin();itx!=vicinity.end();itx++)
    {
        int heuristic = hcost(player->getPosition(),*itx);
        if(heuristic<closest2)
        {
            if((player->getPosition() == *itx))
            {
                toBeAttacked= li.getUnitByPos(*itx);
            }
            else
            {
                closest2=heuristic;
                closestPossible = *itx;
            }

        }

    }


    sel = enem;
    return closestPossible;

}

bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		//Create window
		gWindow = SDL_CreateWindow( "Heroes of the Past", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Create renderer for window
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
            if( gRenderer == NULL )
            {
                printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
                success = false;
            }
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_mage Error: %s\n", IMG_GetError() );
					success = false;
				}
				if( TTF_Init() == -1 )
				{
					printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
					success = false;
				}
			}
		}
	}

	return success;
}

bool itemsInit()
{
    bool success=true;
    if( !itemImage[0].LoadFromFile( "Images/items/bow.png", gRenderer  ) )
	{
		printf( "Failed to load sprite sheet texture!\n" );
		success = false;
	}
	if( !itemImage[1].LoadFromFile( "Images/items/coin.png", gRenderer  ) )
	{
		printf( "Failed to load sprite sheet texture!\n" );
		success = false;
	}
	if( !itemImage[2].LoadFromFile( "Images/items/envelope.png", gRenderer  ) )
	{
		printf( "Failed to load sprite sheet texture!\n" );
		success = false;
	}
	if( !itemImage[3].LoadFromFile( "Images/items/heart.png", gRenderer  ) )
	{
		printf( "Failed to load sprite sheet texture!\n" );
		success = false;
	}
	if( !itemImage[4].LoadFromFile( "Images/items/icon_belt1.png", gRenderer  ) )
	{
		printf( "Failed to load sprite sheet texture!\n" );
		success = false;
	}
	if( !itemImage[5].LoadFromFile( "Images/items/icon_bigclub2.png", gRenderer  ) )
	{
		printf( "Failed to load sprite sheet texture!\n" );
		success = false;
	}
	if( !itemImage[6].LoadFromFile( "Images/items/icon_Bow1.png", gRenderer  ) )
	{
		printf( "Failed to load sprite sheet texture!\n" );
		success = false;
	}
	if( !itemImage[7].LoadFromFile( "Images/items/icon_chain_breast.png", gRenderer  ) )
	{
		printf( "Failed to load sprite sheet texture!\n" );
		success = false;
	}
	if( !itemImage[8].LoadFromFile( "Images/items/icon_chain_helm.png", gRenderer  ) )
	{
		printf( "Failed to load sprite sheet texture!\n" );
		success = false;
	}
	if( !itemImage[9].LoadFromFile( "Images/items/icon_claw3.png", gRenderer  ) )
	{
		printf( "Failed to load sprite sheet texture!\n" );
		success = false;
	}
	if( !itemImage[10].LoadFromFile( "Images/items/icon_halberd2.png", gRenderer  ) )
	{
		printf( "Failed to load sprite sheet texture!\n" );
		success = false;
	}
	if( !itemImage[11].LoadFromFile( "Images/items/icon_LEATHER_boots1.png", gRenderer  ) )
	{
		printf( "Failed to load sprite sheet texture!\n" );
		success = false;
	}
	if( !itemImage[12].LoadFromFile( "Images/items/icon_leather_chest1.png", gRenderer  ) )
	{
		printf( "Failed to load sprite sheet texture!\n" );
		success = false;
	}
	if( !itemImage[13].LoadFromFile( "Images/items/icon_LEATHER_GLOVES1.png", gRenderer  ) )
	{
		printf( "Failed to load sprite sheet texture!\n" );
		success = false;
	}
	if( !itemImage[14].LoadFromFile( "Images/items/icon_ring1_2.png", gRenderer  ) )
	{
		printf( "Failed to load sprite sheet texture!\n" );
		success = false;
	}
	if( !itemImage[15].LoadFromFile( "Images/items/icon_spear1.png", gRenderer  ) )
	{
		printf( "Failed to load sprite sheet texture!\n" );
		success = false;
	}
	if( !itemImage[16].LoadFromFile( "Images/items/icon_sword_short1.png", gRenderer  ) )
	{
		printf( "Failed to load sprite sheet texture!\n" );
		success = false;
	}
	if( !itemImage[17].LoadFromFile( "Images/items/potionBlue.png", gRenderer  ) )
	{
		printf( "Failed to load sprite sheet texture!\n" );
		success = false;
	}
	if( !itemImage[18].LoadFromFile( "Images/items/potionGreen.png", gRenderer  ) )
	{
		printf( "Failed to load sprite sheet texture!\n" );
		success = false;
	}
	if( !itemImage[19].LoadFromFile( "Images/items/upg_dagger.png", gRenderer  ) )
	{
		printf( "Failed to load sprite sheet texture!\n" );
		success = false;
	}
	return success;
}
bool loadMedia()
{
	//Loading success flag
	bool success = true;

	//Load sprite sheet texture
	gFont = TTF_OpenFont( "lazy.ttf", 28 );
	if( gFont == NULL )
	{
		printf( "Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError() );
		success = false;
	}
    if( !itemsInit())
	{
		printf( "Failed to load Tile Image!\n" );
		success=false;

	}
	if( !MuslimSheet[0].LoadFromFile( "Images/mIdle.png", gRenderer  ) )
	{
		printf( "Failed to load sprite sheet texture!\n" );
		success = false;
	}
	if( !MuslimSheet[1].LoadFromFile( "Images/mwalking.png", gRenderer  ) )
	{
		printf( "Failed to load sprite sheet texture!\n" );
		success = false;
	}
	if( !MuslimSheet[2].LoadFromFile( "Images/mhurt.png", gRenderer  ) )
	{
		printf( "Failed to load sprite sheet texture!\n" );
		success = false;
	}
	if( !MuslimSheet[3].LoadFromFile( "Images/mattack.png", gRenderer  ) )
	{
		printf( "Failed to load sprite sheet texture!\n" );
		success = false;
	}
	if( !MuslimSheet[4].LoadFromFile( "Images/mdead2.png", gRenderer  ) )
	{
		printf( "Failed to load sprite sheet texture!\n" );
		success = false;
	}
	if( !SikhSheet[0].LoadFromFile( "Images/sIdle.png", gRenderer  ) )
	{
		printf( "Failed to load sprite sheet texture!\n" );
		success = false;
	}
	if( !SikhSheet[1].LoadFromFile( "Images/sWalking.png", gRenderer  ) )
	{
		printf( "Failed to load sprite sheet texture!\n" );
		success = false;
	}
	if( !SikhSheet[2].LoadFromFile( "Images/sHurt.png", gRenderer  ) )
	{
		printf( "Failed to load sprite sheet texture!\n" );
		success = false;
	}
	if( !SikhSheet[3].LoadFromFile( "Images/sAttack.png", gRenderer  ) )
	{
		printf( "Failed to load sprite sheet texture!\n" );
		success = false;
	}
	if( !SikhSheet[4].LoadFromFile( "Images/sDead.png", gRenderer  ) )
	{
		printf( "Failed to load sprite sheet texture!\n" );
		success = false;
	}


	if( !invIcon.LoadFromFile( "Images/inventoryIcon.png", gRenderer  ) )
	{
		printf( "Failed to load sprite sheet texture!\n" );
		success = false;
	}

    if( !cursImg.LoadFromFile( "Images/cursor.png", gRenderer  ) )
	{
		printf( "Failed to load sprite sheet texture!\n" );
		success = false;
	}
	if( !hurdle.LoadFromFile( "Images/hurdle.png", gRenderer  ) )
	{
		printf( "Failed to load sprite sheet texture!\n" );
		success = false;
	}
	if( !terrain.LoadFromFile( "Images/terrain.png", gRenderer  ) )
	{
		printf( "Failed to load sprite sheet texture!\n" );
		success = false;
	}
	if( !inventoryTexture.LoadFromFile( "Images/inventory.png", gRenderer  ) )
	{
		printf( "Failed to load sprite sheet texture!\n" );
		success = false;
	}
	if( !tImage.LoadFromFile( "Images/tile.png", gRenderer  ) )
	{
		printf( "Failed to load Tile Image!\n" );
		success = false;
	}
	if( !storyPage.LoadFromFile( "Images/Page.png", gRenderer  ) )
	{
		printf( "Failed to load Tile Image!\n" );
		success = false;
	}
	if( !bookIcon.LoadFromFile( "Images/bookIcon.png", gRenderer  ) )
	{
		printf( "Failed to load Tile Image!\n" );
		success = false;
	}
    if( !ms1.LoadFromFile( "Images/ms1.png", gRenderer  ) )
	{
		printf( "Failed to load Tile Image!\n" );
		success = false;
	}

	return success;
}

void close()
{
	//Free loaded images

	sikhImage.Free();
	cursImg.Free();
    TTF_CloseFont( gFont );
	gFont = NULL;
	//Destroy window
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}


