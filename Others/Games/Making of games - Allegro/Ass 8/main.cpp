#include <allegro.h>
#include<iostream>
#include<math.h>
#include"Point.h"
#include"Color.h"
#include"Shape.h"
#include"Circle.h"
#include "Square.h"
#include"LinkedList.h"
#include "historystack.h"
#include "Line.h"
#include "Pixel.h"
#include "objectList.h"
#include "layerStack.h"
#include "Screen.h"

volatile long speed_counter = 0; // A long integer which will store the value of the speed counter.

void increment_speed_counter() // A function to increment the speed counter
{
  speed_counter++; // This will just increment the speed counter by one. :)

}
END_OF_FUNCTION(increment_speed_counter);

enum {POINT=1, LINE=2, RECT=3, CIRCLE=4};

int main(int argc, char* argv[])
{
	if (allegro_init() != 0)
	{
		allegro_message("Cannot initialize Allegro.\n");
		return 1;
	}

	//Set the window title when in a GUI environment
	set_window_title("Practice");

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

	/*Buffer*/
	BITMAP* buffer = create_bitmap(SCREEN_W, SCREEN_H);

	//buttons image initializations
    BITMAP* ciimage = load_bitmap("Images/Circle.bmp",NULL);
    BITMAP* reimage = load_bitmap("Images/Rect.bmp",NULL);
    BITMAP* lineimage = load_bitmap("Images/Line.bmp",NULL);
    BITMAP* poimage = load_bitmap("Images/Point.bmp",NULL);

    //A class that holds all the elements of screen
    Screen* menu = new Screen(ciimage,reimage,lineimage,poimage,0,0);
    int spaceDelay = 0;
    int clickDelay = 0;
    int pridelay = 0;
    int secondclickdelay = 0;
    bool clicked = false;

    int currentPrimitive = CIRCLE;
    LinkedList* hstack = new historystack;
    LinkedList* lilist = new objectList;
    layerStack* layer = new layerStack;

    Color color(255,255,255);

    Point MouseClickPos;
    Point MouseCurrentPos;

    Circle *circle = NULL;
    Square *rect = NULL;
    Line *line = NULL;
    Pixel *pix= NULL;
    layer->Push(lilist,false);
	while(!key[KEY_ESC])
    {

        //Add your game logic here
        while (speed_counter > 0)
        {
            menu->Draw(buffer);
            switch(currentPrimitive)
            {
            case POINT:
                if (mouse_b & 1 && !(menu->Occupied(mouse_x,mouse_y)))    //if left mouse button has been clicked, and the location where it is clicked doesnt contain menu items
                {
                    if(clickDelay > 10)
                    {

                        //Get current mouse position
                        MouseClickPos.x = mouse_x;
                        MouseClickPos.y = mouse_y;

                        //generate new pixel, that is basically of dimension 1
                        pix = new Pixel(MouseClickPos, color);

                        //add the new pixel to the linked list
                        lilist->Push(pix,true);

                        clickDelay = 0;
                    }
                }
                break;
            case LINE:
                if (mouse_b & 1 && !(menu->Occupied(mouse_x,mouse_y)))    //if left mouse button has been clicked
                {   //same is the case for line , except that it checks two clicks (one to make and one to relase)
                    if(clickDelay > 10)
                    {
                        if(clicked == false)    //checks of the clicked state is false
                        {
                            //Get current mouse position
                            MouseClickPos.x = mouse_x;
                            MouseClickPos.y = mouse_y;

                            line = new Line(MouseClickPos, color);
                            //draw new line with default color
                            lilist->Push(line,true);
                            clicked = true;
                        }
                        else
                        {
                            clicked = false;    //sets clicked to false, so that we know that the shape has been created
                        }
                        clickDelay = 0;
                    }
                }
                if(line!=NULL && clicked == true)
                {
                    //Sets line coordinates to xc and yc that are current mouse locations
                    int xc = mouse_x ;
                    int yc = mouse_y ;
                    line->SetCoord(xc,yc);
                }

                break;
            case RECT:
                 if (mouse_b & 1 && !(menu->Occupied(mouse_x,mouse_y)))    //if left mouse button has been clicked
                 {  //Same as above for square
                    if(clickDelay > 10)
                    {
                        if(clicked == false)    //checks of the clicked state is false
                        {
                            //Get current mouse position
                            MouseClickPos.x = mouse_x;
                            MouseClickPos.y = mouse_y;

                            rect = new Square(MouseClickPos, color, 0,0);

                            lilist->Push(rect,true);
                            clicked = true;
                        }
                        else
                        {
                            clicked = false;    //sets clicked to false, so that we know that the circle has been created
                        }
                        clickDelay = 0;
                    }
                }
                if(rect!=NULL && clicked == true)//if Square is not NULL and one click has happened
                {
                    //This code continuously changes square length in real-time
                    int w = mouse_x ;
                    int h = mouse_y ;
                    rect->SetLength(w);
                    rect->SetBreadth(h);
                }

                break;
            case CIRCLE:
                if (mouse_b & 1 && !(menu->Occupied(mouse_x,mouse_y)))    //if left mouse button has been clicked
                {
                    if(clickDelay > 10)
                    {
                        if(clicked == false)    //checks of the clicked state is false
                        {
                            //Get current mouse position
                            MouseClickPos.x = mouse_x;
                            MouseClickPos.y = mouse_y;
                            //draw a circle
                            circle = new Circle(MouseClickPos, color, 0);
                            //set clicked to true so that the circle may change radius in real-time
                            lilist->Push(circle,true);
                            clicked = true;
                        }
                        else
                        {
                            clicked = false;    //sets clicked to false, so that we know that the circle has been created
                        }
                        clickDelay = 0;
                    }
                }
                if(circle!=NULL && clicked == true)//if circle is not NULL and one click has happened
                {
                    //This code continuously changes circle radius in real-time
                    int w = mouse_x - MouseClickPos.x;
                    int h = mouse_y - MouseClickPos.y;
                    int radius = (int)sqrt(w*w + h*h);
                    circle->SetRadius(radius);
                }
                break;
            }
            if(mouse_b & 2 || key[KEY_MINUS])   //if mouse 2 or minus pressed
            {
                if(secondclickdelay>10 && lilist->getTail()!=NULL)
                {
                    hstack->Push(lilist->getTail()->object,false);
                    lilist->Pop();    //do an undo function of linked list (go one step back)
                    secondclickdelay = 0;
                }

            }
            if(key[KEY_PLUS_PAD])   //if mouse pad + is pressed
            {
                if(secondclickdelay>10 && hstack->getTail()!=NULL)
                {
                    lilist->Push(hstack->getTail()->object,false);
                    hstack->Pop();
                    secondclickdelay = 0;
                }

            }



            //gets the current Primative from the menu class, that tells where on screen the mouse is clicked
            currentPrimitive = menu->ClickedBox((mouse_b & 1),mouse_x,mouse_y);

            //if the mouse is clicked on the color buttons, call the pixColor function from screen class
            if((mouse_b & 1) && (mouse_x<32 && mouse_x>0) && (mouse_y<(256+24) && mouse_y>256))
            {
                Color temp = menu->pixColor(buffer,mouse_x,mouse_y);
                color = temp;
            }

            //if Up key is pressed, call the lilistmoveup (we need to call from lilist to determine what is on the tail of list)
            if(key[KEY_UP])
            {

            }

            //if key down is pressed , move the object down
            if(key[KEY_DOWN])
            {
                if(clickDelay > 10)
                {

                    clickDelay=0;
                }

            }
            if(key[KEY_N])
            {
                if(clickDelay > 10)
                {
                    layer->Push(lilist,false);
                    LinkedList* lilist = new objectList;
                    clickDelay = 0;
                }
            }

            if(key[KEY_M])
            {   //removes the list from the layer list, and makes the lilist as the tail of layer list
                if(clickDelay > 10)
                {
                    layer->Pop();
                    LinkedList* lilist = layer->getTail()->object;
                    clickDelay = 0;
                }
            }

            spaceDelay++;
            clickDelay++;
            secondclickdelay++;
            pridelay++;
            speed_counter--;

        }


        //Draw all items in the linked list
        layer->Drawall(buffer);

        //draw the menu
        menu->Draw(buffer);
        show_mouse(buffer);
		draw_sprite(screen, buffer, 0, 0);
		clear_bitmap(buffer);
	}
	//Setting mouse to NULL
	lilist->WriteFile();
	show_mouse(NULL);
	//Cleaning Memory
	delete circle;
	destroy_bitmap(buffer);

	return 0;
	//Allegro will automatically deinitalize itself on exit

}
END_OF_MAIN();


