#include "GroundEnemy.h"

//modify


GroundEnemy::GroundEnemy(float x, float y, float w, float h, int hp, int speed, int score)
    : Enemies(x, y, w, h, hp, speed, score)
{
    velocityY = 0;
    isGrounded = false; //false bcz if it is in sky apply gravty will make it true
}

// Applies gravity to the enemy if they are not standing on a surface
void GroundEnemy::applyGravity(float deltaTime)
{
    if (!isGrounded)
    {
        
        
        velocityY = 0.1f;
        setPosition(getX(), getY() + (velocityY * deltaTime));
    }
    else
    {
        // Reset downward velocity if standing on a platform
        velocityY = 0.0f;
    }
}