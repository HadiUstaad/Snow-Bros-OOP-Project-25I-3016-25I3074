#include "Tornado.h"


Tornado::Tornado(float x, float y) : FlyEnemy(x, y, 45, 45, 5, 70, 200)
{
    throwTimer = 2;          
    throwCooldown = 3;       


    shape.setSize(sf::Vector2f(getWidth(), getHeight()));
    shape.setFillColor(sf::Color::Magenta);     
    shape.setPosition(sf::Vector2f(getX(), getY()));
}


void Tornado::updateMovement(float deltaTime, platform platforms[], int count)
{
    // If snowballed dont move or throw
    if (getSnowball())
        return;

    // flying movement is same as flying enemy
    FlyEnemy::updateMovement(deltaTime, platforms, count);

    throwTimer -= deltaTime *10;

    shape.setPosition(sf::Vector2f(getX(), getY()));
}


bool Tornado::canThrow()
{
    // throws if not snowballed and it is time to throw
    //modify player in range check
   //if () 
    {
        if (throwTimer <= 0 && !getSnowball())
        {
            throwTimer = throwCooldown;     // reset timer
            return true;
        }
    }
    return false;
}


Knife* Tornado::createKnife(float playerX, float playerY)
{
    // Create knife at tornado position aimed at player
    float midx = getX() + (getWidth() / 2);
    float midy = getY() + (getHeight() / 2);
    return new Knife(midx,midy, playerX, playerY);
}


void Tornado::draw(sf::RenderWindow& window)
{
    if (getActive())
    {
        window.draw(shape);
    }
}