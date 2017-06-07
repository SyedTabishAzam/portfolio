#include "Explosion.h"


Explosion::Explosion(BITMAP* image, int frame_width, int frame_height,int checker, int x, int y) : Plane(image, frame_width, frame_height, x, y)
{
    type=-1;    //type of explosion is -1
    sp=0;   //score counter sp (local) is set to 0
    explodeSound = load_sample("Sounds/ImpactSound.wav");   //explosion audio loaded
    ck = checker;   //checker (type of dying object) is stored in ck
    counter->AddGlobal(ck); //this ck is passed to method AddGlobal of score

}

Explosion::~Explosion()
{
    destroy_sample(explodeSound);       //Sound destroyed on destructor
    std::cout<<"Explosion class destroyed"<<endl;
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
            else if(sp<=45)
            {      // for last 5 counts, display the points image on screen
                Score* counter = new Score(image,position.x,position.y);
                counter->Determine(ck); //ck is passed to method determine
                counter->Draw(buffer);  //points are drawn for 5 counts
            }


}

void Explosion::Move()
{
    sp++;   //on every loop, whenever MOVE is called through linked list, an sp counter is increased
    if(sp>45)   //if the counter reaches 30, it is reset to 0
    {
        sp=0;
        alive=false;   //and the alive value is set to false
    }
}


