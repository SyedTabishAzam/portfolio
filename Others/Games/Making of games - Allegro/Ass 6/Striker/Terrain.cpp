#include"Terrain.h"

Terrain::Terrain(BITMAP* image, float x, float y, int startx, int starty)
{
    moveFactor = 0.30f;
    position.x = x;
    position.y = y;
    int numx = SCREEN_W/128 ;
    int numy = SCREEN_H/128 + 2;
    totaltiles = numx * numy;

    tile = new Tile[totaltiles];

    int tilenum = 0;

    for(int i = 0; i< totaltiles; i++)
    {
        if(tilenum > numx)
        {
            starty = starty + 128;
            tilenum = 0;
        }
        tile[i].Initialize(image, 128, 128,(i%(numx+1))*128,starty,(rand() % (int)(12)));
        tilenum++;
    }
}
Terrain::~Terrain()
{
    delete[] tile;
}
void Terrain::Move()
{
    for(int i = 0; i< totaltiles; i++)
    {
        tile[i].Move(0.0f,moveFactor);
    }
    position.y = position.y + moveFactor;
}

void Terrain::Draw(BITMAP* buffer)
{
    for(int i = 0; i< totaltiles; i++)
    {
        tile[i].Draw(buffer);
    }
}

Point* Terrain::GetPosition()
{
    return &position;
}
