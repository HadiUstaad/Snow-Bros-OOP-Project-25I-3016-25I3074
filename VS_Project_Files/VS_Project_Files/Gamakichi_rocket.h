#pragma once
#include "Projectile.h"
#include <SFML/Graphics.hpp>

using namespace std;

// explodes on impact
class GamakichiRocket : public Projectile
{
private:
    sf::RectangleShape shape;
    float maxDistance;          // how far it can travel before exploding
    float distanceTraveled;     
    bool exploded;              

    sf::CircleShape explosionShape;
    float explosionTimer;       // how long the explosion stays on screen

public:
    GamakichiRocket(float x, float y, float vx, float vy);

    ~GamakichiRocket() 
    {
    }

    // override to check max distance and handle explosion
    void updatePosition(float deltaTime) override;

    void draw(sf::RenderWindow& window);

    bool hasExploded();
    // returns explosion bounds for player damage check
    sf::FloatRect getExplosionBounds();
    sf::FloatRect getBounds();
};