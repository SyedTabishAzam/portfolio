#include"LightArmour.h"

LightArmour::~LightArmour()
{
    cout<<"\nLight Armour Destroyed";
}

LightArmour::LightArmour(BITMAP* image, int frame_width, int frame_height, int x, int y): Armour(image, frame_width, frame_height, x, y)
{
    healthAddition = 30;
}

void LightArmour::Draw(BITMAP* buffer)
{
    masked_blit(image, buffer, 64, 0, position.x, position.y, frame_width,frame_height);

}

int LightArmour::GetHealthAddition()
{
    return healthAddition;
}


