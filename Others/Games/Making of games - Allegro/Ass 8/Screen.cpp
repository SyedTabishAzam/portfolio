#include "Screen.h"

Screen::Screen(BITMAP* ci,BITMAP* re,BITMAP* li,BITMAP* pi,float sx,float sy)
{   //Initializer
    startx = sx;
    starty = sy;
    box = 4;
    im1 = ci;
    im2 = re;
    im3 = li;
    im4 = pi;
}

Screen::~Screen()
{
    cout<<"Screen Class Destroyed"<<endl;
}

int Screen::ClickedBox(bool click,float x,float y)
{   //if mouse button is pressd, it basically checks on which box is the mouse key pressed

    if(click)
    {   //according to the dimensions of the box, the box value is returned, every value mapped to a primative

        if((x>=startx && x<=(startx + 64)) && (y>=(starty) && y<=(starty + 64)))
            box= 4;
        if((x>=startx && x<=(startx + 64)) && (y>=(starty+64) && y<=(starty + 128)))
            box= 3;
        if((x>=startx && x<=(startx + 64)) && (y>=(starty+128) && y<=(starty + 192)))
            box= 2;
        if((x>=startx && x<=(startx + 64)) && (y>=(starty+192) && y<=(starty + 256)))
            box= 1;
    }

    return box;

}

void Screen::BoxColors(BITMAP* buffer)
{   //Draws the color graph on the screen, doesnt draw all 256 *256*256, but some for the testing purpose
    int i,j,k;
    for(i=0;i<256;i++)
    {
        for(j=0;j<256;j++)
        {   //Every pixel is drawn from 0 to 32 on x axis, and approx 8 tiles vertically
            putpixel(buffer,i%32,(starty+256)+(int(i/32)),makecol(i,j,0));
            j=j+8;
        }

    }
    for(i=0;i<256;i++)
    {   //next color box
        for(j=0;j<256;j++)
        {
            putpixel(buffer,i%32,(starty+256)+8+(int(i/32)),makecol(0,i,j));
            j=j+8;
        }
    }
    for(i=0;i<256;i++)
    {
        for(j=0;j<256;j++)
        {
            putpixel(buffer,i%32,(starty+256)+16+(int(i/32)),makecol(j,0,i));
            j=j+8;
        }
    }

}
bool Screen::Occupied(float x, float y)
{   //tells if the position on the buffer is occupied by the screen or not
    if((x>=startx && x<=(startx + 64)) && (y>=(starty) && y<=(starty + 256 + 24)))
        return true;
    return false;
}

Color Screen::pixColor(BITMAP* buffer,int mx,int my)
{   //returns the color pixels value, when clicked on the color boxes
    int r, g, b, color_value;
    color_value = getpixel(buffer, mx, my);
    r = getr(color_value);
    g = getg(color_value);
    b = getb(color_value);
    Color color(r,g,b);
    return color;

}
void Screen::Draw(BITMAP* buffer)
{   //draws the buttons on screen, and call the color drawer function
    masked_blit(im1,buffer,0,0,startx,starty,64,64);
    masked_blit(im2,buffer,0,0,startx,starty+64,64,64);
    masked_blit(im3,buffer,0,0,startx,starty+128,64,64);
    masked_blit(im4,buffer,0,0,startx,starty+128+64,64,64);
    BoxColors(buffer);
}
