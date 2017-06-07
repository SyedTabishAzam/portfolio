#include "Writer.h"

Writer::Writer(BITMAP* img,string text,bool smfont,int xposition,int yposition)
{   //Initializes the writer class, taking string to write as input, and x and y position of where to write it
    if(smfont)      //if smallfonts are required, variables are set accordingly
    {
        widthandheight = 32;
        startrow = 336;
    }
    else
    {
        startrow= 144;
        widthandheight = 64;
    }

    image = img;
    this->text=text;
    startx = xposition;
    starty = yposition;
}

void Writer::Draw(BITMAP* buffer)
{
    //for every word in the string, some calculations are done
    int i=0;
    for(i=0;i<text.length();i++)
    {
        int map1= toupper(int(text.at(i))); //firstly, the word is converted to upper letter and its asci value noted
        int map2= map1 - 65;    // every alphabet is mapped on 0,1,2 for A,B,C..
        int map3 = map2 % 13; //    Map3 is the mod of alphabet with 13, since there are 13 columns in image for alphabets, this gives row number
        int map4 = int(map2/13);    //map4 is the column number of alphabet
        masked_blit(image,buffer,(map3*widthandheight),startrow+(map4*widthandheight),startx+((widthandheight-10)*i),starty,widthandheight,widthandheight); //alphabet is then drawn
    }

}
