#pragma once
#include "Projectile.h"


using namespace std;

class Knife : public Projectile
{
private:
    sf::RectangleShape shape;   
    float rotation;             // rotation angle
    float rotationSpeed;     

    sf::Texture texture;
    sf::Sprite sprite;
    sf::IntRect frameRect;

public:
   
    Knife(float x, float y, float targetX, float targetY);

    ~Knife() override = default;

    // override to add rotation into the update
    void updatePosition(float deltaTime) override;

    void draw(sf::RenderWindow& window);

    sf::FloatRect getBounds();
};