#include "PowerUp.h"

using namespace std;


PowerUp::PowerUp(float x, float y, int duration, int cost, int type)
    : GameObject(x, y, true, 30, 30)  // powerups are 30x30 on screen
{
    effectDuration = duration;      
    gemCost = cost;                 
    isDroppedFromEnemy = false;     
    powerType = type;          

    shape.setSize(sf::Vector2f(getWidth(), getHeight()));
    shape.setFillColor(sf::Color::White);       
    shape.setPosition(sf::Vector2f(getX(), getY()));
}


PowerUp::~PowerUp()
{

}
void PowerUp::draw(sf::RenderWindow& window)
{
    if (getActive())
    {
        window.draw(shape);
    }
}

void PowerUp::applyEffect()
{
    setActive(false);
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