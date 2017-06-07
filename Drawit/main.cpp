#include <allegro.h>
#include<iostream>
#include <fstream>
#include<math.h>
#include"LinkedList.h"
#include"Point.h"
#include"Shape.h"
#include"Pixel.h"
#include"Rect.h"

using namespace std;

volatile long speed_counter = 0; // A long integer which will store the value of the speed counter.

void increment_speed_counter() // A function to increment the speed counter
{
  speed_counter++; // This will just increment the speed counter by one. :)

}
END_OF_FUNCTION(increment_speed_counter);

//enum {PIXEL, LINE, RECT, CIRCLE};

int main(int argc, char* argv[])
{
	if (allegro_init() != 0)
	{
		allegro_message("Cannot initialize Allegro.\n");
		return 1;
	}

	//Set the window title when in a GUI environment
	set_window_title("Draw IT!");

	if (install_keyboard()) {
		allegro_message("Cannot initialize keyboard input.\n");
		return 1;
	}

	if (install_timer()) {
		allegro_message("Cannot initialize timer.\n");
		return 1;
	}

	//install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT, "");

	LOCK_VARIABLE(speed_counter); //Used to set the timer - which regulates the game's speed
    LOCK_FUNCTION(increment_speed_counter);
    install_int_ex(increment_speed_counter, BPS_TO_TIMER(60));//Set our BPS

	//set graphics mode, trying all acceptable depths
	set_color_depth(32);

	//int w, h;
	//set_desktop_resolution(&w, &h);
	set_color_depth(desktop_color_depth());

	set_gfx_mode(GFX_SAFE, 800, 600, 0, 0);

	install_mouse();

    cout<<"Width: "<<SCREEN_W<<" Height: "<<SCREEN_H<<endl;
    /** Loading all the sprites for the software **/
	/*Buffer*/
	BITMAP* buffer = create_bitmap(SCREEN_W, SCREEN_H);
	/*Mouse*/
	BITMAP* mouseSprite = load_bitmap("Images/Mouse.bmp", NULL);
	/*Color Grid*/
	BITMAP* colorGrid = create_bitmap(96, 32);

    int rcolor = 256;
    int gcolor = 0;
    int bcolor = 0;







    int spaceDelay = 0;
    int clickDelay = 0;
    bool clicked = false;

    int currentPrimitive = RECT;



    set_mouse_sprite(mouseSprite);
    Point MouseClickPos;
    Point MouseCurrentPos;

    LinkedList<Shape>* objectList = new LinkedList<Shape>;

    //Shape *shape = NULL;

    Rect *rect = NULL;
    Pixel *pixel = NULL;


    bool saveit;
    saveit = false;

	while(!key[KEY_ESC])
    {
        //Add your game logic here
        while (speed_counter > 0)
        {
            if (key[KEY_MINUS] || mouse_b & 2)    //if right mouse button has been clicked, remove the last added object
            {
                if(clickDelay > 10)
                {

                    objectList->Remove();
                    clickDelay = 0;
                }
            }
            if (mouse_b & 1)    //if left mouse button has been clicked
            {
                if(clickDelay > 10)
                {
                    if(clicked == false)    //checks of the clicked state is false
                    {
                        show_mouse(NULL);
                        //Get current mouse position
                        MouseClickPos.x = mouse_x;
                        MouseClickPos.y = mouse_y;

                        switch(currentPrimitive)
                        {
                        case PIXEL:
                            pixel = new Pixel(MouseClickPos);

                            objectList->Insert(pixel);

                            pixel = NULL;
                            break;
                        case RECT:
                            //create a rectangle of zero dimensions
                            rect = new Rect(MouseClickPos, MouseClickPos);
                        }
                        //set clicked to true so that the objects may change dimensions in real-time
                        if(currentPrimitive!=PIXEL)
                            clicked = true;
                    }
                    else
                    {
                        clicked = false;    //sets clicked to false, so that we know that the object has been created
                        switch(currentPrimitive)
                        {
                        case PIXEL:
                            break;
                        case RECT:
                            objectList->Insert(rect);     //passing the object to the linked list
                            rect = NULL;                //set rect to NULL after passing the object to list
                            break;
                        }

                    }
                    clickDelay = 0;
                }
            }
            if(clicked == true)//if shape is not NULL and one click has happened
            {
                switch(currentPrimitive)
                {
                case PIXEL:
                    break;
                case RECT:
                    rect->SetBottomRight(mouse_x, mouse_y); //This code continuously changes bottom right point in real-time
                    break;
                }
            }

            if(key[KEY_E]) // If the user hits the P key, draw a point
            {
                currentPrimitive = PIXEL;
            }
            if(key[KEY_R]) // If the user hits the R key, draw a rectangle
            {
                currentPrimitive = RECT;
            }

            spaceDelay++;
            clickDelay++;

            speed_counter--;
        }
        if(key[KEY_S])
        {
            saveit=true;
            break;
        }
        objectList->Draw(buffer);
        //Only Drawing if circle is not NULL
        //Only Drawing if rect is not NULL
        if(rect != NULL)
            rect->Draw(buffer);
        //Only Drawing if line is not NULL





        //Display mouse
        if(clicked == false)
            show_mouse(buffer);

        //Draw the entire screen
		draw_sprite(screen, buffer, 0, 0);

		//Clear the buffer for redrawing
		clear_bitmap(buffer);
	}
	if(saveit)
        objectList->WriteFile();

	//Setting mouse to NULL
	show_mouse(NULL);
	//Cleaning Memory
	delete objectList;
	destroy_bitmap(buffer);

	return 0;
	//Allegro will automatically deinitalize itself on exit

}
END_OF_MAIN();


