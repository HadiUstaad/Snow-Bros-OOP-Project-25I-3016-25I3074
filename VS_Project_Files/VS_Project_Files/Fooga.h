#pragma once
#include "Flying_Enemy.h"
#include <SFML/Graphics.hpp>

using namespace std;

// Fooga will hover normally and sometimes land on the ground
class Fooga : public FlyEnemy
{
private:
    sf::RectangleShape shape;  
    bool isFlying;              // currently flying or on ground
    float landTimer;            // countdown until landing or takeoff
    bool isGrounded = false;
    float velocityY = 0;

public:
 
    Fooga(float x, float y);

    ~Fooga() override = default;

    // overriding to add landing behaviour
    void updateMovement(float deltaTime, platform platform[], int count) override;
    void applygravity(float deltaTime, platform platform[], int count) ;

    void draw(sf::RenderWindow& window) override;
    
    void attemptLanding();      // tries to land on platform
    void takeoff();      // takes off from ground

    void onHit() override;
    bool isAlive() override;
};