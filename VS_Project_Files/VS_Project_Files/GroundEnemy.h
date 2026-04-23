#pragma once
#include "Enemy.h"

using namespace std;

class GroundEnemy : public Enemies
{
protected:
    float velocityY;   // For falling down platforms
    bool isGrounded;   // To check if they are standing on a floor

public:
    GroundEnemy(float x, float y, float w, float h, int hp, int speed, int score);

    // default is used bcz we have no pointers to delete. it is like making an empty destructor body
    virtual ~GroundEnemy() = default;

    virtual void applyGravity(float deltaTime);

    // Enemy functions ara not overwritten so class is abstract

};
