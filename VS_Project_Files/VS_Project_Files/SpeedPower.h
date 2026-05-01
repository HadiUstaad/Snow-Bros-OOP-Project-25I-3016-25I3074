#pragma once
#include "PowerUp.h"
#include <SFML/Graphics.hpp>

using namespace std;

class SpeedPowerUp : public PowerUp
{
private:  
    float speedMultiplier;          

public:
    SpeedPowerUp(float x, float y, bool dropped);

    ~SpeedPowerUp() override = default;
    
    float getSpeedMultiplier();
};