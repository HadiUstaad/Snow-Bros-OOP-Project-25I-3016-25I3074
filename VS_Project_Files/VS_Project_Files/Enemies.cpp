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

    hitbox.setSize(sf::Vector2f(0, 0));
    hitbox.setFillColor(sf::Color::Transparent);
    hitbox.setOutlineColor(sf::Color::White);  
    hitbox.setOutlineThickness(2);
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

    hitbox.setSize(sf::Vector2f(w, h));          // same size as enemy 
    hitbox.setPosition(sf::Vector2f(x, y));      // same enemy position
    hitbox.setFillColor(sf::Color::Transparent);
    hitbox.setOutlineColor(sf::Color::White);
    hitbox.setOutlineThickness(2);
}

Enemies::~Enemies()
{
}

//void Enemies::onHitBySnowball()
//{
//    // When hit by a player's snowball, take damage or change state
//    isSnowballed = true;
//    movespeed = 0; // Stop moving when snowballed
//}

//void Enemies::onDeath()
//{
//    setActive(false); // Remove from game loop
//
//    // Modify Gem drop logic will go here later
//}


void Enemies::drawHitbox(sf::RenderWindow& window)
{
    // Only draw hitbox if enemy is active (alive)
    if (getActive())
    {
        window.draw(hitbox);
    }
}

// update hitbox to follow enemy's current position
// whwnever enemy moves we call this function too
void Enemies::updateHitboxPosition()
{
    
    hitbox.setPosition(sf::Vector2f(getX(), getY()));
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

//void Enemies::takeDamage(int dmg)
//{
//    health -= dmg;
//    if (health <= 0)
//    {
//        health = 0;
//        onDeath();
//    }
//}

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