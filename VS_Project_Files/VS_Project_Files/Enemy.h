#pragma once
#include"GameObjects.h"

using namespace std;

class Enemies : public GameObject
{
    int health;
    int damage;	// how much damage it will do to player
    float movespeed;
    int scoreValue;
    float gemChance;	// how much chances to drop a gem
    bool isSnowballed; // is completely covered up by snow ball

public:

    Enemies();
    Enemies(float x, float y, float w, float h, int hp, int speed, int score);

    virtual ~Enemies();


    virtual void updateMovement(float deltaTime) = 0;

    virtual void onHitBySnowball();


    virtual void onDeath();


    virtual void draw() = 0;

    
    int getHealth();
    bool getSnowball();
    int getScore();

    void takeDamage(int damage);
    void setSnowball(bool snowball);


};
