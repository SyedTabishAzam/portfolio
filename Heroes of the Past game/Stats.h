#pragma once
#include <sstream>
#include <iostream>

using namespace std;
enum TYPE {NONE,HEAD,SHOULDER1,SHOULDER2,CHEST,WAIST,ELBOW,ARM,FEET,MISC1,MISC2};
struct Stats
{

    float damage;
    float defense;
    float health;
    int type = NONE;
    int speed;
    Stats()
    {
        damage = 0;
        defense = 0;
        health=100;
        speed=1;
        type = NONE;
    }
    string getStringDamage()
    {
        ostringstream ss;
        ss<<damage;
        return ss.str();
    }
    string getStringDefence()
    {
        ostringstream ss;
        ss<<defense;
        return ss.str();
    }

    string getStringSpeed()
    {
        ostringstream ss;
        ss<<speed;
        return ss.str();
    }

    string getStringHealth()
    {
        ostringstream ss;
        ss<<health;
        return ss.str();
    }

    int getType()
    {
        return type;
    }

    Stats operator+(const Stats& s1 )
    {
        Stats out;
        out.damage = this->damage + s1.damage;
        out.defense = this->defense + s1.defense;
        out.speed = this->speed + s1.speed;
        out.health = this->defense + s1.health;
        return out;
    }

};
