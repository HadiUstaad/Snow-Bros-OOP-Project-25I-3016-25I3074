#include "Botom.h"
#include "Ball.h"
#include <ctime>

//Modify add texture


Boton::Boton(float x, float y) : GroundEnemy(x, y, 40, 40, 6, 50, 100) 
{

    froze = false;
    moveDirection = 1;
    shape.setSize(sf::Vector2f(getWidth(), getHeight()));
    shape.setFillColor(sf::Color::Yellow); // Make the Boton yellow for visibility until graphics is added
    shape.setPosition(sf::Vector2f(getX(), getY()));
}

void Boton::updateMovement(float deltaTime, platform platforms[], int count)
{

    if (getSnowball())
        return;

    //check frozen
    if (froze) {
        return;
    }
    // checks if it is in air and then pulls it down until it reaches a ground
    applyGravity(deltaTime, platforms, count);

    // walks horizontally on ground. no vertical movement
    if (isGrounded)
    {
        float newX = getX() + (moveDirection * getSpeed() * deltaTime);

        // screen boundary reversal check
        if (newX <= 0 || newX >= 800 - getWidth())
        {
            moveDirection *= -1;
            newX = getX() + (moveDirection * getSpeed() * deltaTime);
        }

        // checks that if it is at edge. it creates a variable probe which stores 1 pixel left position
        // ahead of boton. if that place has air it will either fal or reverse direction
        // if it is grounded it will keep moving in its direcetion

        float probeY = getY() + getHeight() + 1.0f;   // one pixel below feet
        float probeX;
        if (moveDirection > 0)
        {
            probeX = newX + getWidth();
        }
        else
        {
            probeX = newX - 1;
        }

        bool groundAhead = false;
        for (int i = 0; i < count; i++)
        {
            sf::Vector2f pPos = platforms[i].getBody().getPosition();
            sf::Vector2f pSize = platforms[i].getBody().getSize();

            bool inX = false;
            bool inY = false;
            if (probeX >= pPos.x && probeX <= pPos.x + pSize.x)
            {
                inX = true;
            }
            if (probeY >= pPos.y && probeY <= pPos.y + pSize.y)
            {
                inY = 1;
            }
           
            if (inX && inY)
            {
                groundAhead = true;
                break;
            }
        }

        if (groundAhead)
        {
            setPosition(newX, getY());
        }
        else
        {
            
            srand(time(0));

            // no ground ahead then reverse direction and try that way instead
            // or you can fall of. this is random
            if (rand() % 2 == 0)
            {
                moveDirection *= -1;
                float reverseX = getX() + (moveDirection * getSpeed() * deltaTime);
                setPosition(reverseX, getY());
            }
            else
            {
                setPosition(newX, getY());
            }
            
        }
    }
   
    shape.setPosition(sf::Vector2f(getX(), getY()));
}

// cant override as no window parameter
void Boton::draw()
{
  
}


void Boton::draw(sf::RenderWindow& window)
{
    // Only draw if the enemy is active/alive
    if (getActive())
    {
        window.draw(shape);
    }
}

sf::FloatRect Boton::getBounds() {
    return shape.getGlobalBounds();
}


//freezing functions

void Boton::freeze() {

    froze = true;
    shape.setFillColor(sf::Color::Cyan);
}

bool Boton::checkfreeze() {
    return froze;
}