#include "SpeedPower.h"


SpeedPowerUp::SpeedPowerUp(float x, float y, bool dropped)
    : PowerUp(x, y, 5, 50, 0)  // lasts 5 sec costs 50 gems type 0
{
    speedMultiplier = 1.5f;         // makes player 50 percent faster
    isDroppedFromEnemy = dropped;   // set drop status

    shape.setFillColor(sf::Color::Green);       // green for speed
    
}


float SpeedPowerUp::getSpeedMultiplier()
{
    return speedMultiplier;
}