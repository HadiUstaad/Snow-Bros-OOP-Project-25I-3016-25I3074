#pragma once
#include "Enemy.h"
#include "Platform.h"

using namespace std;

// Base class for all enemies that can fly in the air
// Inherits from Enemies (Level 3 in hierarchy)
class FlyEnemy : public Enemies
{
protected:
    float amplitude;        // how far up and down they move
    float frequency;        // how fast they oscillate up down
    float timeCounter;      // keeps track of time for sine wave movement
    float hoverHeight;      // the base height where enemy hovers around

public:
    
    FlyEnemy(float x, float y, float w, float h, int hp, int speed, int score);

    
    virtual ~FlyEnemy() = default;

    // flying enemies dont need gravity bcz of the sine wave movement but still need to update movement
    virtual void updateMovement(float deltaTime, platform platform[], int count);

    
    virtual void draw() = 0;

};
