#include "Knife.h"
#include <cmath>


Knife::Knife(float x, float y, float targetX, float targetY)
    : Projectile(x, y, 0, 0, 1)  // velocity is calculated below and damage is 1
{
    // direction to target (player)
    float dx = targetX - x; 
    float dy = targetY - y; 

    // Calculate distance to target by euclidean norm
    float distance = sqrt(dx * dx + dy * dy); 

    // avoid division by zero so we lock minimum deistance to 1
    if (distance < 1)
    {
        distance = 1;
    }

    // set speed. the velocity is normalized or unit vector is taken and then multiplie by speed magnitude
    float speed = 100;       // pixels per second
    velocityX = (dx / distance) * speed;
    velocityY = (dy / distance) * speed;

    // set rotation speed of knife and the angle
    rotation = 0;
    rotationSpeed = 180;     


    shape.setSize(sf::Vector2f(15, 5));         
    shape.setFillColor(sf::Color::White);
    shape.setOrigin(sf::Vector2f(7.5f, 2.5f));   // origin for rotation or center is middle of knife
    shape.setPosition(sf::Vector2f(x, y));
}


// position update as a normal projectile but rotaion is added additionally
void Knife::updatePosition(float deltaTime)
{
    Projectile::updatePosition(deltaTime);

    rotation += rotationSpeed * deltaTime;

    // Keep rotation in 0-360 range otherwise we wont see rotation as it will be very fast
    if (rotation >= 360)
    {
        rotation = rotation- 360;
    }

    shape.setPosition(sf::Vector2f(getX(), getY()));
    shape.setRotation(sf::degrees(rotation)); // rotation is in degrees as why not
}


// Draws knife on window
void Knife::draw(sf::RenderWindow& window)
{
    if (getActive())
    {
        window.draw(shape);
    }
}