
#include <allegro.h>
#include "Ship.h"
#include <iostream>

using namespace std;

int main(int argc, char* argv[])
{


    //allegro default initializations
    if (allegro_init() != 0)
    {
        allegro_message("Cannot initialize Allegro.\n");
        return 1;
    }

    //Set the window title when in a GUI environment
    set_window_title("Ship");

    if (install_keyboard()) {
        allegro_message("Cannot initialize keyboard input.\n");
        return 1;
    }

    //set graphics mode, trying all acceptable depths
    set_color_depth(32);

    int w, h;
    get_desktop_resolution(&w, &h);
    set_color_depth(desktop_color_depth());
    //allegro tries all the depths of screen
    if (set_gfx_mode(GFX_AUTODETECT_FULLSCREEN, w, h, 0, 0))
    {
        set_color_depth(24);
        if (set_gfx_mode(GFX_AUTODETECT_FULLSCREEN, w, h, 0, 0))
        {
            set_color_depth(16);
            if (set_gfx_mode(GFX_AUTODETECT_FULLSCREEN, w, h, 0, 0))
            {
                set_color_depth(15);
                if (set_gfx_mode(GFX_AUTODETECT_FULLSCREEN, w, h, 0, 0))
                {
                    allegro_message("Video Error: %s.\n", allegro_error);
                    return 1;
                }
            }
        }
    }

    BITMAP* buffer = create_bitmap(SCREEN_W, SCREEN_H);

    BITMAP* waterImage;
    waterImage = load_bitmap("Images/Water.bmp", NULL); //loads waterimage as bitmap in a variable

    if(waterImage == NULL)
    {
        allegro_message("could not load water image");
        allegro_exit();
    }

    BITMAP* shipImage;
    shipImage = load_bitmap("images/ship.bmp", NULL);       //loads ship image as bitmap in variable

    if(shipImage == NULL)
    {
        allegro_message("could not load ship image");
        allegro_exit();
    }
   BITMAP* turretImage;
   turretImage = load_bitmap("images/turret.bmp", NULL);   //loads turret image

    if(turretImage == NULL)
    {
        allegro_message("could not load turret image");
        allegro_exit();
    }

    Ship ship;      //creates a new object of type ship


    ship.Initialize(shipImage,turretImage,w/2,h/2); //initializes ship, giving the ship and turret image as arguments

    float xm = w/2;     //defines xm to be half of horizontal width
    float ym = h/2;     //defines ym to be half of vertical height
    float rot = 0;      //a new variable used to rotate the turrets
    //Wait for a key to be pressed
    while (!key[KEY_ESC])//(!keypressed())      //until and unless ESC key is not pressed, do the following
    {
        draw_sprite(buffer, waterImage, 0, 0);      //draw the water image on the canvas
        ship.Draw(buffer,rot);                      //calls the method DRAW in ship
        rot = rot+1;                                //on every loop, add 1 to rot
        draw_sprite(screen, buffer, 0, 0);
        clear_bitmap(buffer);

        if(ym>0){                               //checks if the height is 0, i.e the ship's top is touching the screen
            ym = ym - 1;                        //if not, then reduce height by 1, to make ship move
        }

        ship.SetPosition(xm,ym);                //changes the position of ship everytime (horizontal x remains same)
        rest(5);
    }

    return 0;
  //Allegro will automatically deinitalize itself on exit*/
}
END_OF_MAIN()
