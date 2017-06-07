
#include <allegro.h>
#include "square.h"
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
    set_window_title("Board");

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

    BITMAP* squareImg;          //loads the image of square
    squareImg = load_bitmap("Images/sprite.bmp", NULL); //loads squareimage as bitmap in a variable

    if(squareImg == NULL)
    {
        allegro_message("could not load water image");      //produce error if it cant be loaded
        allegro_exit();
    }

    BITMAP* border;
    border= load_bitmap("Images/border.bmp",NULL);          //loads border image


   /* IMPLEMENTATION 1: */
    Square square[64] = squareImg;      //creates a new object array of type SQUARE and gives is default argument

   /* IMPLEMENTATION 2: */
   // Square *square;                     //creates a pointer of type square
   // square = new Square[64]  ;          //allocates 64 memory spaces to this pointer
   // for(int i = 0;i<64;i++){
   //     square[i].Initialize(squareImg); //initializes square, giving the square its image as arguments (true is just to differentiate between IMPLEMENTATIONS)
   // }

    //Wait for a key to be pressed
    while (!key[KEY_ESC])//(!keypressed())      //until and unless ESC key is not pressed, do the following
    {
        int c=0;
        int r=-1;
        draw_sprite(buffer, border, 0, 0);      //draw the border image on the canvas
        for(int i = 0;i<64;i++){
            if(r<7){                           //helping variables to extract sprite
                int a=r++;
                cout<<a;
                r++;

                }
                else{
                r=0;
                c++;
                }
                square[i].Draw(buffer,r,c);                      //calls the method DRAW in square,

        }
        draw_sprite(screen, buffer, 0, 0);
        clear_bitmap(buffer);




        rest(5);
    }

    return 0;
  //Allegro will automatically deinitalize itself on exit*/
}
END_OF_MAIN()
