#pragma once
#include "Enemy.h"

using namespace std;

class GroundEnemy : public Enemies
{
protected:
    float velocityY;   // For falling down platforms
    bool isGrounded;   // To check if they are standing on a floor

public:
    // Constructor chaining to Enemies
    GroundEnemy(float x, float y, float w, float h, int hp, int speed, int score);

    virtual ~GroundEnemy() = default;

    // Abstract methods inherited from Enemies are left unimplemented here, 
    // ensuring GroundEnemy remains an abstract class.

    // A specific virtual method for ground enemies
    virtual void applyGravity(float deltaTime);

};
