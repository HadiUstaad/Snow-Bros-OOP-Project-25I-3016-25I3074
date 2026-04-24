#include "GroundEnemy.h"




GroundEnemy::GroundEnemy(float x, float y, float w, float h, int hp, int speed, int score)
    : Enemies(x, y, w, h, hp, speed, score)
{
    velocityY = 0;
    isGrounded = false; //false bcz if it is in sky apply gravty will make it true
}

// Applies gravity to the enemy if they are not standing on a surface
void GroundEnemy::applyGravity(float deltaTime, platform platform[], int count)
{
    
    if (!isGrounded)
    {
        float max_velocity = 2500;
        float gravity = 1000;
        velocityY += gravity * deltaTime*100;
        if (velocityY > max_velocity)
        {
            velocityY = max_velocity;
        }
        
    }

    float newY = getY() + velocityY * deltaTime;
    setPosition(getX(), newY);

    //  check landing on any platform
    isGrounded = false;

    float ex = getX();          // enemy x starting point
    float ey = getY();          // enemy y starting point (in sfml +y axis is downwards)
    float ew = getWidth();      // x + ew will give the position of ending horizontal of enemy
    float eh = getHeight();

    for (int i = 0; i < count; i++)
    {
        // stores position and size of each platform one by one
        sf::Vector2f pPos = platform[i].getBody().getPosition();
        sf::Vector2f pSize = platform[i].getBody().getSize();

        // horizontal overlap of enmey with platform
        bool overlapX = (ex + ew > pPos.x) && (ex < pPos.x + pSize.x);
        if (!overlapX) continue;

        // check if enemy bottom crossed the platforms top
        float enemyBottom = ey + eh;
        float prevBottom = enemyBottom - velocityY * deltaTime;   // where bottom was

        // it chec
        bool crossedTop = (prevBottom <= pPos.y + 2.0f) && (enemyBottom >= pPos.y);

        if (crossedTop)
        {
            // snap enemy to platform surface so perfectly aligned
            setPosition(getX(), pPos.y - eh);
            velocityY = 0;
            isGrounded = true;
            break;
        }
    }
    
    
    //  if standing on a platform no downward speed
    velocityY = 0;
    
}