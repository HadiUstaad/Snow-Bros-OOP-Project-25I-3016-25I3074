#pragma once
#include"GameObjects.h"
#include "Platform.h"
#include <SFML/Graphics.hpp>

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


    virtual void updateMovement(float deltaTime,platform platform[],int count) = 0;

    virtual void onHitBySnowball();


    virtual void onDeath();

    virtual void draw(sf::RenderWindow & window) = 0;

    
    int getHealth();
    bool getSnowball();
    int getScore();
    float getSpeed();
        
    void takeDamage(int damage);
    void setSnowball(bool snowball);
    void setSpeed(float s);
    



};
