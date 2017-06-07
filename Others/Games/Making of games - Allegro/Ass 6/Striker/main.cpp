#include <allegro.h>

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


	BITMAP* buffer = create_bitmap(SCREEN_W, SCREEN_H);


    int spaceDelay = 0;
	while(!key[KEY_ESC])
    {
        //Add your game logic here

        while (speed_counter > 0)
        {

            if(key[KEY_RIGHT]) // If the user hits the right key, change the picture's X coordinate
            {
            }
            if(key[KEY_LEFT]) // Ditto' - only for left key
            {
            }
            if(key[KEY_UP]) // If the user hits the up key, change the picture's Y coordinate
            {
            }
            if(key[KEY_DOWN]) // Ditto' - only for down
            {
            }
            if(key[KEY_SPACE]) // press space to fire
            {

                if(spaceDelay >= 20)
                {


                }

            }


            spaceDelay++;



            speed_counter--;


        }



		draw_sprite(screen, buffer, 0, 0);
		clear_bitmap(buffer);




    }
	destroy_bitmap(buffer);

}
END_OF_MAIN();

