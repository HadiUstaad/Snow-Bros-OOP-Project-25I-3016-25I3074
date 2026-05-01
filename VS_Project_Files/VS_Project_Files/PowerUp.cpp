#include "PowerUp.h"

using namespace std;


PowerUp::PowerUp(float x, float y, int duration, int cost, int type)
    : GameObject(x, y, true, 30, 30)  // powerups are 30x30 on screen
{
    effectDuration = duration;      
    gemCost = cost;                 
    isDroppedFromEnemy = false;     
    powerType = type;               
}


PowerUp::~PowerUp()
{

}

int PowerUp::getDuration()
{
    return effectDuration;
}

int PowerUp::getCost()
{
    return gemCost;
}

bool PowerUp::isDropped()
{
    return isDroppedFromEnemy;
}

int PowerUp::getType()
{
    return powerType;
}