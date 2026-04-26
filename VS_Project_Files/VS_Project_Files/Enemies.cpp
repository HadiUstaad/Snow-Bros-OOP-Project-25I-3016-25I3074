#include "Enemy.h"
#include <iostream>




Enemies::Enemies() : GameObject(0, 0, false, 0, 0)
{
    health = 6;
    damage = 1;
    movespeed = 30;
    scoreValue = 100;
    gemChance = 0.2f;
    isSnowballed = false;
}

Enemies::Enemies(float x, float y, float w, float h, int hp, int speed, int score)
    : GameObject(x, y, true, w, h) 
   
{
    health = hp;
    damage = 1;
    movespeed = speed;
    scoreValue = score;
    gemChance = 0.2f;
    isSnowballed = false;
}

Enemies::~Enemies()
{
}

void Enemies::onHitBySnowball()
{
    // When hit by a player's snowball, take damage or change state
    isSnowballed = true;
    movespeed = 0; // Stop moving when snowballed
}

void Enemies::onDeath()
{
    setActive(false); // Remove from game loop

    // Modify Gem drop logic will go here later
}

int Enemies::getHealth() 
{ 
    return health; 
}
bool Enemies::getSnowball() 
{ 
    return isSnowballed; 
}
int Enemies::getScore() 
{ 
    return scoreValue; 
}

void Enemies::takeDamage(int dmg)
{
    health -= dmg;
    if (health <= 0)
    {
        health = 0;
        onDeath();
    }
}

void Enemies::setSnowball(bool snowball)
{
    isSnowballed = snowball;
}

float Enemies::getSpeed()
{
    return movespeed;
}

void Enemies::setSpeed(float s)
{
    movespeed = s;
}