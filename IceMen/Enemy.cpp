#include "Enemy.h"

Enemy::Enemy()
{
    stepper=0;
    ran = rand()%100;
    stepcomplete=false;
    health = 10000;
    iceball = NORMAL;
    damage=1;
    ballhealth = 6;
    dfact = 1;
}
Enemy::~Enemy()
{
    cout<<"Enemy Object destroyed"<<endl;
}

Object* Enemy::InstantDeath()
{
    health=0;
    setAlive(false);
    Powerup* pup = new Powerup(image,x,y,15,19);
    return pup;
}

void Enemy::Move()
{
    if(health<10000 && iceball != BALLMOVE)
    {
        health++;
        ChangeState();
    }
    if(stepcomplete==true)
    {
        ran = rand()%100;
        stepcomplete=false;
    }

    if(iceball==NORMAL)
    {
        if(ran<50)
        {
            if(stepper<900)
            {
                float tempx= x;
                direction=LEFT;
                ChangePosition(x - 0.1,y);
                if(tempx==x)
                    stepper=900;
                stepper++;
            }
            else
            {
                stepper =0;
                stepcomplete = true;
            }
        }
        else
        {
            if(stepper<900)
            {
                float tempx=x;
                direction=RIGHT;
                ChangePosition(x + 0.1,y);
                if(tempx==x)
                    stepper = 900;
                stepper++;
            }
            else
            {
                stepper =0;
                stepcomplete = true;
            }
        }
    }
    if(iceball==BALLMOVE)
    {
        type=4;
        float tempx = x;
        ChangePosition(x+dfact,y);
        ApplyGravity();
        if(tempx == x)
        {
            dfact = dfact* -1;
            ballhealth = ballhealth-1;
            if(ballhealth==0)
            {
                setAlive(false);

            }
        }
    }
    ApplyGravity();

}

void Enemy::TakeDamage(int dam)
{
    if(GetHealth()>0)
        health = health - dam;
    ChangeState();
}

int Enemy::GetState()
{
    return iceball;
}

void Enemy::ChangeState(int ice,int sp)
{
    if(ice==6)
    {
        iceball = BALLMOVE;
    }
}





