#include "Botom.h"
#include "Ball.h"
#include <ctime>

//Modify add texture


Boton::Boton(float x, float y) : GroundEnemy(x, y, 40, 40, 300, 50, 100) 
{

    froze = false;
    alive = true;
    moveDirection = 1;

    movespeed = 150;

    shape.setSize(sf::Vector2f(getWidth(), getHeight()));
    shape.setFillColor(sf::Color::Yellow); // Make the Boton yellow for visibility until graphics is added
    shape.setPosition(sf::Vector2f(getX(), getY()));
}

void Boton::updateMovement(float deltaTime, platform platforms[], int count)
{

    if (getSnowball() || froze || !alive)
        return;


  
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

           
            bool inX = (probeX >= pPos.x && probeX <= pPos.x + pSize.x);
            bool inY = (probeY >= pPos.y && probeY <= pPos.y + pSize.y);
           
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
            
            
            setPosition(newX, getY());
            isGrounded = false;   // important
            
        }

    }
   
    shape.setPosition(sf::Vector2f(getX(), getY()));
    // makes hitbox at the same positon as sprite
    updateHitboxPosition();
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


//Eliminating functions
void Boton::onHit() {

    if (!froze) {
        freeze();
    }
    else {
        alive = false;
        setActive(false);
    }
}

bool Boton::isAlive() {
    return alive;
}

void Boton::draw(sf::RenderWindow& window)
{
    if (alive && getActive())
    {
        window.draw(shape);
    }
}

// modify to solve hitbox error
void Boton::drawHitbox(sf::RenderWindow& window)
{
    // only draws hitbox when enemy is alive and active
    // this prevents the bug when hitbox was remaining after object destroyed
    if (alive && getActive())
    {
        window.draw(hitbox);
    }
}

