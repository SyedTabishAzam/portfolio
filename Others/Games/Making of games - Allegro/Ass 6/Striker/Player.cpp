#include"Player.h"
#include"Bullet.h"

Player::Player(BITMAP* image, int frame_width, int frame_height, Point position) : Plane(image, frame_width, frame_height, position)
{
    type=1;
    maxHealth = 100;
    health=100;
    SetHealth(100);
    currentArmour = 0;
    //initial bullet type is 2
    bullettype = 2;
    //initialize object of healthbar
    healthbar = new HealthBar(image,30,40);
    yellcount=0;
    pupSound = load_sample("Sounds/Powerup.wav");


}

Player::Player(BITMAP* image, int frame_width, int frame_height, int x, int y) : Plane(image, frame_width, frame_height, x, y)
{

    healthbar = new HealthBar(image,30,40);
    type=1;
    maxHealth = 100;
    health=100;
    SetHealth(100);
    bullettype = 2;
    currentArmour = 0;
    yellcount=0;
    pupSound = load_sample("Sounds/Powerup.wav");
}

Player::~Player()
{
    delete armour;
}
void Player::UsePuP(int pup)
{   //destroy previous instance of sound and create new instance on use of pup
    destroy_sample(pupSound);
    pupSound = load_sample("Sounds/Powerup.wav");
    //if yellow powerup is picked, call method ChangeBullet, else call method CreateArmour
    (pup==YELLOW) ? (ChangeBullet(pup)) : (CreateArmour(pup));
    play_sample(pupSound, 255, 128, 1000, 0);   //this check ensures that the sound is played only once in the beginning of collision

}

void Player::ChangeBullet(int btype)
{   //Method called when yellow powerup picked
    if(yellcount<2)
    {
        bullettype=bullettype + 1;  //increase bullettype by 1
        if(bullettype>8)    //when bullettype reaches 8 (8 because there are 8 type of bullets)
            bullettype = 3; //reset the bulletcount to 3
        yellcount = yellcount + 1;  //increase yellow pup count everytime powerup is picked
    }
    else
    {//if more thn two powerups are picked, change bullettype to 9 (Missile Implementation)
        bullettype = 9;
    }
}

void Player::CreateArmour(int currentArmour)
{
    if(this->currentArmour > 1)
    {
        delete armour;
        armour=NULL;
        maxHealth = 100;
    }
    this->currentArmour = currentArmour;
    if(currentArmour == LIGHT)
    {//Create object of light armour if LIGHT powerup is picked

        armour = new LightArmour(image, frame_width, frame_height, position.x, position.y);

    }
    else if(currentArmour == HEAVY)
    {//esle create object of Heavy Armour

        armour = new HeavyArmour(image, frame_width, frame_height, position.x, position.y);

    }

    maxHealth = maxHealth + armour->GetHealthAddition();    //maxhealth isw the current maximum health + armour health
    //if currenthealth + armour health exceeds maxhealth, reset it to max health. else let it increase
    ((GetHealth() + armour->GetHealthAddition())>maxHealth) ? (SetHealth(maxHealth)) : (SetHealth(GetHealth() + armour->GetHealthAddition()));



}

void Player::Draw(BITMAP* buffer, bool debug)
{

    //healthbar is drawn
    healthbar->Draw(buffer);

    masked_blit(image, buffer, 0, 0, position.x, position.y, frame_width,frame_height);

    if (currentArmour > 1)
    {
        armour->Draw(buffer);
    }

    if(debug == true)
    {
        line(buffer, position.x,position.y, position.x+frame_width,position.y, makecol(255, 0, 0));
        line(buffer, position.x+frame_width,position.y, position.x+frame_width,position.y+frame_height, makecol(255, 0, 0));
        line(buffer, position.x,position.y+frame_height, position.x+frame_width,position.y+frame_height, makecol(255, 0, 0));
        line(buffer, position.x,position.y+frame_height, position.x,position.y, makecol(255, 0, 0));
    }
}

void Player::SetVelocityX(float vx)
{
    velx = vx;
}

void Player::SetVelocityY(float vy)
{
    vely = vy;
}

void Player::Move()
{
    velx = velx * 0.97f;
    vely = vely * 0.97f;

    Move(velx, vely);

}

void Player::Move(float x, float y)
{

    //healthbar movement(Determined by the player's health, and max health)
    healthbar->Move(GetHealth(),maxHealth);
    position.x = position.x + x;
    position.y = position.y + y;
    if(position.x<0)
    {
        position.x = 0;
    }

    if(position.x>SCREEN_W - GetFrameWidth())
    {
        position.x = SCREEN_W - GetFrameWidth();
    }

    if(position.y<0)
    {
        position.y = 0;
    }

    if(position.y>SCREEN_H - GetFrameHeight())
    {
        position.y = SCREEN_H - GetFrameHeight();
    }

    if(currentArmour>1)
    {
        armour->SetPosition(position.x, position.y);
    }
}

void Player::SetPosition(Point* position)
{
    this->position.x = position->x - frame_width/2;
    this->position.y = position->y - frame_height/2;
    if(currentArmour>0)
    {
        armour->SetPosition(this->position.x, this->position.y);
    }
}

void Player::SetPosition(float x, float y)
{
    this->position.x = x - frame_width/2;
    this->position.y = y - frame_height/2;
    if(currentArmour>0)
    {
        armour->SetPosition(this->position.x, this->position.y);
    }
}

Object* Player::Fire()
{
    //create object of fire, pass it dimensions, image, and type i.e Bullettype(lesser than 10)
    Bullet* bullet = new Bullet(this->image, 16, 16,bullettype ,this->position.x + GetFrameWidth()/2, this->position.y);
    return bullet;
}
