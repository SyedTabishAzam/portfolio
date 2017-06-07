#include <allegro.h>
#include"Point.h"
#include"Player.h"
#include"Viper.h"
#include "Cobra.h"
#include"Bullet.h"
#include"Terrain.h"
#include"LinkedList.h"
#include<iostream>

volatile long speed_counter = 0; // A long integer which will store the value of the speed counter.
volatile long objectCounter = 0;
void increment_speed_counter() // A function to increment the speed counter
{
  speed_counter++; // This will just increment the speed counter by one. :)
  objectCounter++;
}
END_OF_FUNCTION(increment_speed_counter);

const int move_factor = 3;
Player* fighter;

void CreateObjects(LinkedList*, BITMAP*);

int main(int argc, char* argv[])
{
	if (allegro_init() != 0)
	{
		allegro_message("Cannot initialize Allegro.\n");
		return 1;
	}

	//Set the window title when in a GUI environment
	set_window_title("Striker");

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


	/*Plane Image*/
	BITMAP* gameSprite = load_bitmap("Images/gameSprite.bmp", NULL);

    srand((unsigned)time(0));


    SAMPLE *fireSound ;
    fireSound = load_sample("Sounds/fireSound.wav"); // or .voc


    LinkedList* objects = new LinkedList;   //New linked list

    fighter = new Player(gameSprite, 64, 64, SCREEN_W/2, SCREEN_H - 96);
    objects->Append(fighter);       //Fighter( Our plane) is appended to head of link list. this fact is important for my implementation



    Terrain* terrainTop = new Terrain(gameSprite, 0, -640, 0, -640);
    Terrain* terrainBottom = new Terrain(gameSprite, 0, 0, 0, 0);


    int spaceDelay = 0;


	while(!key[KEY_ESC] && ((objects->GetHead()->object)==fighter)) //Game loops until ESC is pressed , or the head is not fighter anymore, that means fighter is dead
    {
        //Add your game logic here

        while (speed_counter > 0)
        {
            if(key[KEY_RIGHT]) // If the user hits the right key, change the picture's X coordinate
            {
                fighter->SetVelocityX(move_factor);
            }
            if(key[KEY_LEFT]) // Ditto' - only for left key
            {
                fighter->SetVelocityX(-move_factor);
            }
            if(key[KEY_UP]) // If the user hits the up key, change the picture's Y coordinate
            {
                fighter->SetVelocityY(-move_factor);
            }
            if(key[KEY_DOWN]) // Ditto' - only for down
            {
                fighter->SetVelocityY(move_factor);
            }
            if(key[KEY_SPACE]) // press space to fire
            {

                if(spaceDelay >= 20)
                {
                    objects->Append(fighter->Fire());
                    play_sample(fireSound, 255, 128, 1000, 0);
                    spaceDelay = 0;
                }

            }
            terrainTop->Move();
            terrainBottom->Move();
            CreateObjects(objects, gameSprite);
            objects->MoveAll();
            objects->CheckCollision(gameSprite);        //Checks for collision in the linked list

            spaceDelay++;

            if(terrainTop->GetPosition()->y>640)
            {
                cout<<"\nTerrainTop Y:"<<terrainTop->GetPosition()->y;
                delete terrainTop;
                terrainTop = new Terrain(gameSprite, 0, -640, 0, -640);
            }
            if(terrainBottom->GetPosition()->y>640)
            {
                cout<<"\nTerrainBottom Y:"<<terrainBottom->GetPosition()->y;
                delete terrainBottom;
                terrainBottom = new Terrain(gameSprite, 0, -640, 0, -640);
            }

            speed_counter--;


        }



        terrainBottom->Draw(buffer);
        terrainTop->Draw(buffer);
        objects->DrawAll(buffer, true); //Everything is drawn on every loop

		draw_sprite(screen, buffer, 0, 0);
		clear_bitmap(buffer);
		objects->CleanAll();

    }
	//Cleaning Memory
	if((objects->GetHead()->object)!=fighter)   //If the fighter died, quit the game and output a message
    {
        cout<<"Game Over, fighter Dead"<<endl;
	}
	destroy_bitmap(buffer);
	destroy_bitmap(gameSprite);
	delete terrainTop;
	delete terrainBottom;
	delete objects;

	return 0;
	//Allegro will automatically deinitalize itself on exit

}
END_OF_MAIN();

void CreateObjects(LinkedList* objects, BITMAP* gameSprite)
{
    if(objectCounter%250 == 0)
    {
        Viper* viper = new Viper(gameSprite, 64, 64, (rand() % (int)(SCREEN_W)), -128); //a new enemy object viper is created randomly on screen
        Cobra* cobra = new Cobra(gameSprite,64,64,(rand() % (int)(SCREEN_W)),-128); //a new enemey object cobra is created randomly on screen
        cobra->SetTarget(fighter);  //both's target are set to our plane, to compare their movement with
        viper->SetTarget(fighter);
        objects->Append(cobra); //both are appended to the linked list
        objects->Append(viper);
    }
}
