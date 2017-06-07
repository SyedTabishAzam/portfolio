
#include <allegro.h>
#include "square.h"
#include <iostream>
#include "piece.h"
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
    install_mouse();
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

    BITMAP* Img;          //loads the image of square
    Img = load_bitmap("Images/sprite.bmp", NULL); //loads squareimage as bitmap in a variable

    if(Img == NULL)
    {
        allegro_message("could not load image");      //produce error if it cant be loaded
        allegro_exit();
    }

    BITMAP* border;
    border= load_bitmap("Images/border.bmp",NULL);          //loads border image

   /* IMPLEMENTATION 1: */
    Square square[64];      //creates a new object array of type SQUARE and gives is default argument
    piece pis[24];
   /* IMPLEMENTATION 2: */
   // Square *square;                     //creates a pointer of type square
   // square = new Square[64]  ;          //allocates 64 memory spaces to this pointer
    for(int i = 0;i<64;i++){
        square[i].setImage(Img);     //initializes square, giving the square its image as arguments (true is just to differentiate between IMPLEMENTATIONS)
        square[i].setOccupied(false);

    }



    int pos, xx, yy,k;
    k=0;                    //k is used to initialize only the needed memory of pieces i.e 24
    bool initflag = false;      //initializer flag
    while (!key[KEY_ESC])   //(!keypressed())      //until and unless ESC key is not pressed, do the following
    {

        if(initflag==false){    //initializes only if the flag is false
            int c=0;
            int r=-1;
            draw_sprite(buffer, border, 0, 0);      //draw the border image on the canvas
            for(int j=0;j<64;j++){
                if(r<7){                            //helping variables to extract sprite
                        r++;
                    }
                    else{
                        r=0;
                        c++;
                    }
                    square[j].setPosition(r,c);                 //the jth square is provided with its rows and columns
                    square[j].draw(buffer);                     //calls the method DRAW in square,

                    if((r+c)%2==1 && (j<24 || j>39)){           //initialize the piece only if the the piece is on odd number of square, and only initializes for above 12 and below 12 pieces
                        pis[k].setKing(false);                  //king for every square is set to false
                        if(j<24){                                //if the piece are below 24, that means they are on top of the board
                            pis[k].initPiece(r,c,Img,true);     //so initialize them with white color
                            square[j].setOccupied(true);
                        }
                        else{
                            pis[k].initPiece(r,c,Img,false);    //else if they are on bottom, initialize them with black
                            square[j].setOccupied(true);        //set the occupied to true
                        }
                        pis[k].draw(buffer);
                        square[j].setPiece(k);                  //set every square's piece to the piece it is carrying
                        k++;                                    // add 1 to k after every initialization of piece
                    }
                    else{
                        square[j].setPiece(-1);                 //if piece is not being initialized, set the piece number to -1
                    }


            }
            initflag=true;                          //after first initialization, flag is set to false, so that it doesnt initialize again and again

        }
        show_mouse(screen);                         //command to show pointer on screen
        set_mouse_range(30,30, 512, 512);           //and lock its range

        if (mouse_b & 1){                           //execute the following IF mouse 1 is pressed
            pos = mouse_pos;
            xx = pos >> 16;
            yy = pos & 0x0000ffff;                  //checking for coordinates where mouse is clicked (default allegro)

            int fromx = ((xx)-30)/64;               //selected x coordinates converted to rows
            int fromy = ((yy)-30)/64;               //selected y coordinates converted to columns


            int selectedpiece = (fromx + (8*(fromy)));       //getting piece number on the selected square



            point to;                                        //declaring a point for target location


            bool fl=false;                                  //flag explained below
            int targetlocation;

            while((!(mouse_b & 2)) && (square[selectedpiece].getOccupied()==true) ){ //loop until mouse 2 is not pressed after mouse press 1 is detected, or until we select a square where there lies a piece
                pos = mouse_pos;
                int tx = pos >> 16;
                int ty = pos & 0x0000ffff;
                to.x=((tx)-30)/64;                          //determines the x coordinates converted to row for target location
                to.y=((ty)-30)/64;
                targetlocation = (to.x + (8*(to.y)));       //target location's sequential number

                fl = true;                                  //flag that triggers the condition that mouse 2 is pressed and the selected square had a piece
            }

            if(fl==true && square[targetlocation].getOccupied()==false && ((to.x+to.y)%2==1)){  //if above condition is met and if the target location is not the adjacent location
                square[selectedpiece].setPosition(fromx,fromy);
                square[selectedpiece].setOccupied(false);               //sets occupied of the selected piece to false

                square[selectedpiece].draw(buffer);

                int currentpiece = square[selectedpiece].getPiece();    //current piece is the piece that is on the selected square
                pis[currentpiece].moveTo(&to);                          //move the piece to target location

                if((pis[currentpiece].white==false) && (targetlocation>=0 && targetlocation<=7)) {  //if the piece is black, and it reaches top boundry, then it becomes king
                        pis[currentpiece].setKing(true);
                        cout<<"king white"<<endl;
                }
                else if((pis[currentpiece].white==true)&& (targetlocation>=56 && targetlocation<=63)){  //if the piece is white, and it reaches bottom boundry, then it becomes king
                        pis[currentpiece].setKing(true);
                        cout<<"king black"<<endl;
                }
                else{
                        pis[currentpiece].setKing(pis[currentpiece].isKing());     //else the piece's previous state is followed
                }

                pis[currentpiece].draw(buffer);
                square[targetlocation].setPiece(square[selectedpiece].getPiece()); //set the target locations square piece to selected squares current piece
                square[selectedpiece].setPiece(-1);                                //selected square now has no piece, so the piece number on square is -1
                square[targetlocation].setOccupied(true);                          //since the target location has a piece, its set occupied is set to true
            }

        }

        draw_sprite(screen, buffer, 0, 0);





        rest(5);
    }
    clear_bitmap(buffer);
    return 0;
  //Allegro will automatically deinitalize itself on exit*/
}
END_OF_MAIN()
