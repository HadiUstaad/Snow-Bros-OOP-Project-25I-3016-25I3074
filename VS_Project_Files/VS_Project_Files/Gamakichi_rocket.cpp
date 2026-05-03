#include "Gamakichi_rocket.h"
#include <cmath>


GamakichiRocket::GamakichiRocket(float x, float y, float vx, float vy)
    : Projectile(x, y, vx, vy, 1)      // damage is 1 life
{
    maxDistance = 350;       
    distanceTraveled = 0;
    exploded = false;
    explosionTimer = 0.5f;   

    
    shape.setSize(sf::Vector2f(20, 8));
    shape.setFillColor(sf::Color(255, 100, 0));   // orange rocket
    shape.setOrigin(sf::Vector2f(10, 4));
    shape.setPosition(sf::Vector2f(x, y));

    // explosion is a bigger circle
    explosionShape.setRadius(40);
    explosionShape.setFillColor(sf::Color(255, 60, 0, 160));    // semi transparent orange
    explosionShape.setOrigin(sf::Vector2f(40, 40));
    explosionShape.setPosition(sf::Vector2f(x, y));
}


void GamakichiRocket::updatePosition(float deltaTime)
{
    // if exploded just count down the explosion timer and we will not update position
    if (exploded)
    {
        explosionTimer -= deltaTime;
        if (explosionTimer <= 0)
        {
            setActive(false);  
        }
        return;
    }

    // move like update in projectile
    Projectile::updatePosition(deltaTime);

    // track distance by distance formula sqrt(a^2 + b^2)
    float dx = velocityX * deltaTime;       // this give velocity in small fram. small frame add up to get totaal distance
    float dy = velocityY * deltaTime;
    distanceTraveled += sqrt(dx * dx + dy * dy);

    // shapes position is equal to the gameobjects pos
    shape.setPosition(sf::Vector2f(getX(), getY()));

  

    // check if max distance reached then explode
    if (distanceTraveled >= maxDistance)
    {
        exploded = true;
        explosionShape.setPosition(sf::Vector2f(getX(), getY()));
        hasHitTarget = true;    // stop movement
    }
}


void GamakichiRocket::draw(sf::RenderWindow& window)
{
    if (!getActive())
    {
        return;
    }

    if (exploded)
    {
        window.draw(explosionShape);
    }
    else
    {
        window.draw(shape);
    }
}


bool GamakichiRocket::hasExploded()
{
    return exploded;
}


sf::FloatRect GamakichiRocket::getExplosionBounds()
{
    return explosionShape.getGlobalBounds();
}

sf::FloatRect GamakichiRocket::getBounds()
{
    return shape.getGlobalBounds();
}