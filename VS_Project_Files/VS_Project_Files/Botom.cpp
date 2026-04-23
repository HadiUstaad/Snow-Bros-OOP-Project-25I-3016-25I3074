#include "Botom.h"

//Modify add texture


Boton::Boton(float x, float y) : GroundEnemy(x, y, 40, 40, 6, 50, 100)
{
    moveDirection = 1;
    shape.setSize(sf::Vector2f(getWidth(), getHeight()));
    shape.setFillColor(sf::Color::Red); // Make the Boton red for visibility until graphics is added
    shape.setPosition(sf::Vector2f(getX(), getY()));
}

void Boton::updateMovement(float deltaTime)
{
    // If the enemy is encased in a snowball, it shouldn't move
    if (getSnowball())
    {
        return;
    }

    
    applyGravity(deltaTime);

    // modify AI
    float newX = getX() + (moveDirection * getSpeed() * deltaTime);

    // temporary logic to keep moving right until it reaches the end
    if (newX <= 0 || newX >= 800 - getWidth())
    {
        moveDirection *= -1; // Reverse direction 
        newX = getX() + (moveDirection * getSpeed() * deltaTime);
    }

    // update the position as it moves
    setPosition(newX, getY());
    shape.setPosition(sf::Vector2f(getX(), getY()));
    // the rectangle wwill be seen at new position
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