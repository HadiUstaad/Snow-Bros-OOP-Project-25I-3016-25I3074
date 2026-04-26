#pragma once
#include "Projectile.h"


using namespace std;

class Knife : public Projectile
{
private:
    sf::RectangleShape shape;   
    float rotation;             // rotation angle
    float rotationSpeed;        

public:
   
    Knife(float x, float y, float targetX, float targetY);

    ~Knife() override = default;

    // override to add rotation into the update
    void updatePosition(float deltaTime) override;

    void draw(sf::RenderWindow& window);
};