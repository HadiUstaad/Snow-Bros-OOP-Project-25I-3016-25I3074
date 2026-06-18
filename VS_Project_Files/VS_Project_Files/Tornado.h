#pragma once
#include "Flying_Enemy.h"
#include "Knife.h"
#include <SFML/Graphics.hpp>
#include<iostream>

using namespace std;





// enemy flies and throws knife at player
class Tornado : public FlyEnemy
{
private:
    sf::RectangleShape shape;      
    float throwTimer;               // counting time so we can throw
    float throwCooldown;            // no infinite knife throwing
    bool alive;
    bool froze;
    bool isGrounded = false;
    int moveDirection = 1;
    float velocityY = 0;
    

    sf::Texture texture;
    sf::Sprite sprite;
    sf::IntRect frameRect;

    sf::Texture snowball;
public:

    Tornado(float x, float y);

    ~Tornado() override = default;

    // add throwing knife 
    void updateMovement(float deltaTime, platform platform[], int count) override;
    void applygravity(float deltaTime, platform platform[], int count);


    void drawHitbox(sf::RenderWindow& window) override;

    void draw(sf::RenderWindow& window);

    void freeze();
    bool checkfreeze();
    sf::FloatRect getBounds();

    
    bool canThrow();                    // checks if ready to throw
    Knife* createKnife(float playerX, float playerY);  // creates new knife aimed at player

    // elimination logic
    void onHit() override;
    bool isAlive() override;


};