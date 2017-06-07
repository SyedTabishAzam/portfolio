#include "Map.h"

Map::Map()
{

}

Map::~Map()
{
    cout<<"Map Destroyed"<<endl;
}

void Map::GetSpecs(vector<Object*> &ob,vector<Object*> &em,BITMAP* image)
{
    ifstream file1("level1.txt");
    string line;
    stringstream token;
    getline(file1,line);
    token<<line;
    int hurdles;
    token>>hurdles;
    Object* hurds[hurdles+3];
    hurds[0] = new Hurdles(image,0,SCREEN_H,SCREEN_W,1);
    hurds[1] = new Hurdles(image,0,0,1,SCREEN_H);
    hurds[2] = new Hurdles(image,SCREEN_W-1,0,1,SCREEN_H);
    ob.push_back(hurds[0]);
    ob.push_back(hurds[1]);
    ob.push_back(hurds[2]);
    for(int i=2;i<hurdles+2;i++)
    {
        getline(file1,line);
        token.str("");
        token.clear();
        token<<line;

        int x;
        int y;
        token>>x;
        token>>y;

        getline(file1,line);
        token.str("");
        token.clear();
        token<<line;
        int width;
        int height;
        string wandh = token.str();
        if(wandh.substr(0,wandh.find(" "))=="SCREEN_W")
        {
            token>>width;
            width = SCREEN_W;
        }
        else
        {
            token>>width;
        }

        if(wandh.substr(wandh.find(" ")+1)=="SCREEN_H")
        {
            token>>height;
            height = SCREEN_H;
        }
        else
        {
            token>>height;
        }


        hurds[i] = new Hurdles(image,x,y,width,height);
        ob.push_back(hurds[i]);

    }
    token.clear();
    getline(file1,line);
    token<<line;
    int enemies;
    token>>enemies;
    Object* enem[enemies];
    BITMAP* gameSprite = load_bitmap("Images/snowbros3.bmp", NULL);
    for(int j=0;j<enemies;j++)
    {
        getline(file1,line);
        token.str("");
        token.clear();
        token<<line;

        int x,y,type;

        token>>type>>x>>y;
        if(type==11)
        {
            enem[j] = new FlameThrower(gameSprite,x,y,51,41);
        }
        em.push_back(enem[j]);

    }

}

void Map::ChangeLevel()
{

}
