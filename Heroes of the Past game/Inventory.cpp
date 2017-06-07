#include "Inventory.h"

Inventory::Inventory(LTexture* inventoryImage)
{
    Image = inventoryImage;
    counter = 0;
    x=30;
    y=30;

}

Stats Inventory::getStat()
{
    Stats n;
    int x = 0;
    Item* current;
    while ( items.ElementAt(x) != NULL)
    {
        current = items.ElementAt(x);
        x++;
        n = n + current->GetStats();
    }

    return n;
}

void Inventory::addItem(Item* it)
{

    if (it->GetStats().type==NONE || occupied[it->GetStats().type])
    {
        int placeX =  43 + (counter % 6) * 40;
        int placeY =  265 + int(counter/6) * 40;
        counter++;
        it->setCoordinates(placeX,placeY);
    }
    else
    {
        addToSpecial(it);
    }
    items.Push(it);
}

void Inventory::addToSpecial(Item*& it)
{
    int Ltype = it->GetStats().type;

    if(Ltype==HEAD)
    {
        it->setCoordinates(122+x,30+y);
    }
    else if(Ltype==SHOULDER1)
    {
        it->setCoordinates(92+x,53+y);
    }
    else if(Ltype==SHOULDER2)
    {
        it->setCoordinates(155+x,30+y);
    }
    else if(Ltype==CHEST)
    {
        it->setCoordinates(118+x,60+y);
    }
    else if(Ltype==ARM)
    {
        it->setCoordinates(156+x,98+y);
    }
    else if(Ltype==FEET)
    {
        it->setCoordinates(120+x,163+y);
    }
    else if(Ltype==WAIST)
    {
        it->setCoordinates(120+x,102+y);
    }
    else if(Ltype==ELBOW)
    {
        it->setCoordinates(81+x,81+y);
    }
    else if(Ltype==MISC1)
    {
        it->setCoordinates(84+x,105+y);
    }
    else if(Ltype==MISC2)
    {
        it->setCoordinates(170+x,107+y);
    }
    occupied[Ltype]=true;
}

Item* Inventory::getItem()
{
    counter--;
    Item* item = items.Pop();
    return items.Pop();
}

void Inventory::Render(SDL_Renderer* gRenderer)
{
    Image->Render( x, y,NULL, 0.0, NULL, SDL_FLIP_NONE, gRenderer );

    items.RenderAll(gRenderer);
}

void Inventory::showStats(SDL_Renderer* gRenderer)
{
    Stats stat = getStat();
    string damage = "Damage: " + stat.getStringDamage();
    string defence = "Defence: " + stat.getStringDefence();
    string speed = "Speed: " + stat.getStringSpeed();

    drawText(damage,10,450,gRenderer);
    drawText(defence,200,450,gRenderer);
    drawText(speed,10,480,gRenderer);

}

void Inventory::drawText(string text,int x,int y, SDL_Renderer* gRenderer)
{

		//Render text
    extern TTF_Font *gFont;

    SDL_Color textColor = { 255, 255, 255 };

    if( !gTextTexture.loadFromRenderedText( text,gFont, textColor, gRenderer ) )
    {
        printf( "Failed to render text texture!\n" );

    }
    else
    {
        gTextTexture.Render( x, y, NULL, 0.0, NULL, SDL_FLIP_NONE, gRenderer );

    }

}

