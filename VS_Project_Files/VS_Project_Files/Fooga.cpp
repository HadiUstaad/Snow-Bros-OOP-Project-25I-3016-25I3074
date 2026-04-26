#include "Fooga.h"
#include "Platform.h"
#include <ctime>

Fooga::Fooga(float x, float y) : FlyEnemy(x, y, 40, 40, 4, 60, 150)
{
    isFlying = true; // starts in air
    landTimer = 25; // will attempt landing after 3 seconds

    setSpeed(15);
    shape.setSize(sf::Vector2f(getWidth(), getHeight()));
    shape.setFillColor(sf::Color::Green);    
    shape.setPosition(sf::Vector2f(getX(), getY()));
}


void Fooga::updateMovement(float deltaTime, platform platforms[], int count)
{
    // If snowballed dont move
    if (getSnowball())
        return;

    // decrease timer until it will be 0
    landTimer -= deltaTime;

    // if flying update hover motion , else apply gravity logic
    if (isFlying)
    {
        // call parent flying movement
        FlyEnemy::updateMovement(deltaTime, platforms, count);

        // check if time to land
        if (landTimer <= 0)
        {
            attemptLanding();
            landTimer = 20;   // stay grounded for 2 seconds
        }
    }
    else
    {
        applygravity(deltaTime, platforms, count);
        // On ground just move horizontally
        float newX = getX() + (getSpeed() * deltaTime);

        // Reverse at edges
        if (newX <= 0 || newX >= 800 - getWidth())
        {
            setSpeed(-getSpeed());
            newX = getX() + (getSpeed() * deltaTime);
        }

        setPosition(newX, getY());

        // Check if time to takeoff
        if (landTimer <= 0)
        {
            takeoff();
            landTimer = 25;   
        }
    }

    // Update visual position
    shape.setPosition(sf::Vector2f(getX(), getY()));
}



void Fooga::draw(sf::RenderWindow& window)
{
    if (getActive())
    {
        window.draw(shape);
    }
}

// attempts to land on nearest platform below
void Fooga::attemptLanding()
{
    // Modify for now just land at current position
    // In full version would check if platform then land below but this will be later added as an extra
    isFlying = false;
}

// Takes off from ground back into air
void Fooga::takeoff()
{
    isFlying = true;
    hoverHeight = getY()-90;   // set new hover center at current height
}

void Fooga::applygravity(float deltaTime, platform platforms[], int count)
{

    if (!isFlying)
    {

        if (!isGrounded)
        {
            float max_velocity = 2500;
            float gravity = 1000;
            velocityY += gravity * deltaTime * 100;
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
            sf::Vector2f pPos = platforms[i].getBody().getPosition();
            sf::Vector2f pSize = platforms[i].getBody().getSize();

            // horizontal overlap of enmey with platform
            bool overlapX = (ex + ew > pPos.x) && (ex < pPos.x + pSize.x);
            if (!overlapX)
            {
                continue;
            }

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
        velocityY = 0;

    }
}