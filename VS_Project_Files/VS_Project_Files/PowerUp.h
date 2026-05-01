#pragma once
#include "GameObjects.h"

using namespace std;

class PowerUp : public GameObject
{
protected:
    sf::RectangleShape shape;
    int effectDuration;        
    int gemCost;               
    bool isDroppedFromEnemy;    
    int powerType;             

public:
    PowerUp(float x, float y, int duration, int cost, int type);

    virtual ~PowerUp();

    virtual void applyEffect();

    virtual void draw(sf::RenderWindow& window);

    int getDuration();            
    int getCost();                
    bool isDropped();              
    int getType();
};