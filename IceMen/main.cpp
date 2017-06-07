#include <allegro.h>
#include<iostream>
#include "SnowMan.h"
#include "FlameThrower.h"
#include "LinkedList.cpp"
#include <cstdlib>
#include "time.h"
#include "Map.h"
#include "vector"
#include "BackgroundGame.h"
#include "Powerup.h"

using namespace std;
volatile long speed_counter = 0; // A long integer which will store the value of the speed counter.
volatile long objectCounter = 0;

void initMap(LinkedList<Object*>*,BITMAP*,BITMAP*,BITMAP*,SnowMan**);
void Loadit(LinkedList<Object*>*,BITMAP*,BITMAP*,SnowMan**);
vector<Object*> grounds;
void increment_speed_counter() // A function to increment the speed counter
{
  speed_counter++; // This will just increment the speed counter by one. :)
  objectCounter++;
}
END_OF_FUNCTION(increment_speed_counter);

int main(int argc, char* argv[])
{
    srand(time(0));
	if (allegro_init() != 0)
	{
		allegro_message("Cannot initialize Allegro.\n");
		return 1;
	}

	//Set the window title when in a GUI environment
	set_window_title("IceMen");

	if (install_keyboard()) {
		allegro_message("Cannot initialize keyboard input.\n");
		return 1;
	}

	if (install_timer()) {
		allegro_message("Cannot initialize timer.\n");
		return 1;
	}

	install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT, "");

	LOCK_VARIABLE(speed_counter); //Used to set the timer - which regulates the game's speed
    LOCK_FUNCTION(increment_speed_counter);
    install_int_ex(increment_speed_counter, BPS_TO_TIMER(60));//Set our BPS

	//set graphics mode, trying all acceptable depths
	set_color_depth(32);

	int w, h;
	get_desktop_resolution(&w, &h);
	set_color_depth(desktop_color_depth());

	set_gfx_mode(GFX_SAFE, 800, 600, 0, 0);

	/*Buffer*/
	BITMAP* buffer = create_bitmap(SCREEN_W, SCREEN_H);



	BITMAP* gameSprite = load_bitmap("Images/snowbros3.bmp", NULL);
    BITMAP* background = load_bitmap("Images/backdrop.bmp",NULL);
    srand((unsigned)time(0));


    SnowMan* snow;
    int spaceDelay = 0;
    unsigned int jk = 0;
    cout<<((jk-6)&&0);
    LinkedList<Object*> *li = new LinkedList<Object*>;


    float oth = 0;
    bool flag=false;
    BITMAP* hu = load_bitmap("Images/hurdle2.bmp", NULL);

    initMap(li,hu,gameSprite,buffer,&snow);
    BackgroundGame* bg = new BackgroundGame(background,0,0);
    //ft = 0;
    //li->Push(ft);
    //li->Push(snow);
	while(!key[KEY_ESC])
    {
        //Add your game logic here

        while (speed_counter > 0)
        {
            if(key[KEY_RIGHT])
            {
                snow->ChangeState(RIGHT,oth);
            }
            else if(key[KEY_LEFT])
            {
                snow->ChangeState(LEFT,oth);
            }
            else
            {
                snow->ChangeState(FREE,oth);
            }
            if(key[KEY_UP])
            {
                if(spaceDelay>=30)
                {
                   snow->ChangeState(JUMP,oth);
                   flag = true;
                   spaceDelay=0;
                }


            }
            else if(key[KEY_DOWN])
            {

            }


            if(key[KEY_U])
            {
                if(spaceDelay>=30)
                {
                    Object* pup = new Powerup(gameSprite,450,SCREEN_H-30,15,19);
                    li->Push(pup);
                    spaceDelay = 0;
                }
            }
            if(key[KEY_SPACE])
            {

                if(spaceDelay >= 20)
                {
                    li->Push(snow->Fire());
                    spaceDelay = 0;
                }

            }


            spaceDelay++;
            speed_counter--;
            if(flag==true)
            {
                oth++;
                if(oth==31.0)
                {
                    oth=0;
                    flag = false;
                }
            }





        }
    li->Update();

    bg->Draw(buffer);
    li->Draw(buffer);
    li->CheckCollision();

    draw_sprite(screen, buffer, 0, 0);
    clear_bitmap(buffer);
    li->CleanAll();

	}
	//Cleaning Memory
	li->Save();
	destroy_bitmap(buffer);
	destroy_bitmap(gameSprite);



	return 0;
	//Allegro will automatically deinitalize itself on exit

}
END_OF_MAIN();


void initMap(LinkedList<Object*>* li,BITMAP* image,BITMAP* gameSprite,BITMAP* buffer, SnowMan** sn)
{
    Map* level = new Map;
    int menutype=1;
    int drawer1 = 0;

    while (true)
    {

        masked_blit(gameSprite,buffer,12,117,(SCREEN_W/2)-40,(SCREEN_H/2)-9,80,18);
        masked_blit(gameSprite,buffer,12,134,(SCREEN_W/2)-40,(SCREEN_H/2)+18-9,82,18);
        masked_blit(gameSprite,buffer,295,13,(SCREEN_W/2)-60,(SCREEN_H/2)+drawer1-9,15,21);
        if(key[KEY_DOWN])
        {
            menutype=2;
            drawer1=18;
        }
        if(key[KEY_UP])
        {
            menutype=1;
            drawer1=0;
        }
        if(key[KEY_ENTER])
        {
            if(menutype==1)
            {
                vector<Object*> obstacles;
                vector<Object*> enemies;
                level->GetSpecs(obstacles,enemies,image);
                vector<Object*>::iterator it;
                for(it = obstacles.begin();it!=obstacles.end();it++)
                {
                    li->Push(*it);
                }
                for(it = enemies.begin();it!=enemies.end();it++)
                {
                    li->Push(*it);
                }
                *sn = new SnowMan(gameSprite,450,SCREEN_H-64,36,53);
                li->Push(*sn);
                extern vector<Object*> grounds;
                grounds = obstacles;
            }
            else if(menutype==2)
            {
                Loadit(li,gameSprite,image,sn);
            }
            break;
        }
        draw_sprite(screen, buffer, 0, 0);
        clear_bitmap(buffer);
    }



}

void Loadit(LinkedList<Object*>* li,BITMAP* gameSprite, BITMAP* hurdl,SnowMan** sn)
{
    ifstream pFile;
    pFile.open("save.txt",std::fstream::in);
    string line,classname;

    while (line!="$")
    {
        getline(pFile,line);

        bool garbage = true;
        Object* temp;

        if (line.find("FlameThrower") != std::string::npos)
        {
            garbage = false;
            temp = new FlameThrower(gameSprite,30,30,51,41);
            temp->Load(pFile);
            li->Push(temp);
        }
        if (line.find("Hurdles") != std::string::npos)
        {
            extern vector<Object*> grounds;
            garbage = false;
            temp = new Hurdles(hurdl,35,40,36,53);
            temp->Load(pFile);
            grounds.push_back(temp);
            li->Push(temp);
        }
        if (line.find("SnowMan") != std::string::npos)
        {

            garbage = false;
            *sn = new SnowMan(gameSprite,450,SCREEN_H-64,36,53);
            temp = *sn;
            temp->Load(pFile);
            li->Push(temp);
        }
        if(garbage!=true)
        {
            //temp->Load(pFile);
        }
        getline(pFile,line);

    }

    pFile.close();
}
END_OF_FUNCTION();
