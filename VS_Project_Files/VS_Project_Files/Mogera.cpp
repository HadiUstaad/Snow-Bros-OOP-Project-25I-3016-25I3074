#include "Mogera.h"



Mogera::Mogera(float x, float y) : Boss(x, y, 80, 80, 30, 1000)
{
    childCount = 0;           
    maxChildPerPhase = 4;        
    spawnTimer = 4;             

    
    shape.setSize(sf::Vector2f(getWidth(), getHeight()));
    shape.setFillColor(sf::Color::Magenta);         
    shape.setPosition(sf::Vector2f(getX(), getY()));
}

void Mogera::updateMovement(float deltaTime, platform platform[], int count)
{
    if (!alive)
    {
        return;
    }
    updateHitboxPosition();
}


void Mogera::updatePhase(float deltaTime)
{
    if (getSnowball())
    {
        return;
    }

    setPhaseTimer(getPhaseTimer() + deltaTime * 100) ;

    spawnTimer -= deltaTime * 100;

    // Different behavior in different phase
    if (getCurrentPhase() == 1)
    {
        // child should spawn if timer is 0 and number of child are less than max child
        if (spawnTimer <= 0 && (childCount < maxChildPerPhase))
        {
            spawnMinions();
            spawnTimer = 4;     
            maxChildPerPhase = 4;
        }
    }
    else if (getCurrentPhase() == 2)
    {
       
        if (spawnTimer <= 0 && (childCount < maxChildPerPhase))
        {
            spawnMinions();
            spawnTimer = 2.5f;   
            maxChildPerPhase = 5;
        }
    }
    else if (getCurrentPhase() == 3)
    {
        
        if (spawnTimer <= 0 && (childCount < maxChildPerPhase))
        {
            spawnMinions();
            spawnTimer = 1.5f;     
            maxChildPerPhase = 6;
        }
    }
}




void Mogera::spawnMinions()
{
   
    childCount++;

    // If reached max no minions will spawn. if it does it means next phase started so child = 0;
    if (childCount >= maxChildPerPhase)
    {
        childCount = 0;
    }
}


void Mogera::draw(sf::RenderWindow& window)
{
    if (getActive())
    {
        window.draw(shape);
    }
}

void Mogera::drawHitbox(sf::RenderWindow& window)
{
    if (alive && getActive())
    {
        window.draw(hitbox);
    }
}

bool Mogera::isAlive()
{
    return alive;
}

void Mogera::onHit()
{

}