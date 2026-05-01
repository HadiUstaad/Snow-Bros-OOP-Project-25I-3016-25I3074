#pragma once
#include "PowerUp.h"
#include <SFML/Graphics.hpp>

using namespace std;

class SpeedPowerUp : public PowerUp
{
private:
    sf::RectangleShape shape;      
    float speedMultiplier;          

public:
    SpeedPowerUp(float x, float y, bool dropped);

    ~SpeedPowerUp() override = default;

    void applyEffect() override;
    
    void draw(sf::RenderWindow& window);

    float getSpeedMultiplier();
};