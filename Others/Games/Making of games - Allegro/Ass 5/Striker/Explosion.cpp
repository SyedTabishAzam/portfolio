#include "Explosion.h"

Explosion::Explosion(BITMAP* image, int frame_width, int frame_height, Point position) : Plane(image, frame_width, frame_height, position)
{   //Constructor the calls the constructor of Plane (just like bullet)
     type=-1;   //Type of explosion is Exclusive, that is a negative number
     sp=0;      //an explosion counter used to delaw the frames of explosion
     explodeSound = load_sample("Sounds/ImpactSound.wav");  //loads sound
}

Explosion::Explosion(BITMAP* image, int frame_width, int frame_height, int x, int y) : Plane(image, frame_width, frame_height, x, y)
{
    type=-1;
    sp=0;
    explodeSound = load_sample("Sounds/ImpactSound.wav");
}

Explosion::~Explosion()
{
    std::cout<<"Explosion class destroyed";
}

void Explosion::Draw(BITMAP* buffer,bool debug)
{
            if (sp==1)
            {
                play_sample(explodeSound, 255, 128, 1000, 0);   //this check ensures that the sound is played only once in the beginning of collision
            }
            if(sp<=5)       //for every sp count uptil +5, one frame is displayed. this ensures frames doesnt run too fast
                masked_blit(image, buffer, 0, 688, position.x, position.y,46 ,46);
            else if(sp<=10)
                masked_blit(image, buffer, 46, 688,position.x, position.y,46 ,46);
            else if(sp<=15)
                masked_blit(image, buffer, 92, 688, position.x, position.y,46 ,46);
            else if(sp<=20)
                masked_blit(image, buffer, 138, 688,position.x, position.y,46 ,46);
            else if(sp<=25)
                masked_blit(image, buffer, 184, 688,position.x, position.y,46 ,46);
            else if(sp<=30)
                masked_blit(image, buffer, 230, 688,position.x, position.y,46 ,46);

}

void Explosion::Move()
{
    sp++;   //on every loop, whenever MOVE is called through linked list, an sp counter is increased
    if(sp>30)   //if the counter reaches 30, it is reset to 0
    {
        sp=0;
        alive=false;   //and the alive value is set to false
    }
}
