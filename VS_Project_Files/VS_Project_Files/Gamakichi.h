#pragma once
#include "Boss.h"
#include "Gamakichi_rocket.h"
#include <SFML/Graphics.hpp>

using namespace std;


class Gamakichi : public Boss
{
private:
    sf::RectangleShape shape;

    // rocket storage. max 8 rockets on screen at once
    GamakichiRocket* rockets[8];
    int rocketCount;

    float fireTimer;
    float fireCooldown;         

    int childCount;
    float spawnTimer;
    float spawnCooldown;

    bool alive;

    // tracks where we last saw the player for aiming
    // iski wajah se rocket jo bas seedhi line mei jaa raha tha wo masla hal hua hai
    float lastPlayerX;
    float lastPlayerY;

public:
    Gamakichi(float x, float y);

    ~Gamakichi() override;

    void updatePhase(float deltaTime) override;

    // fires rockets at angles based on current phase
    void fireRockets(float playerX, float playerY);

    void spawnMinions() override;

    void updateMovement(float deltaTime, platform platform[], int count) override;

    void draw(sf::RenderWindow& window) override;

    void drawHitbox(sf::RenderWindow& window) override;

    //returns the array of where the rocket is stored
    GamakichiRocket** getRockets();
    int getRocketCount();

    void onHit() override;
    bool isAlive() override;
};