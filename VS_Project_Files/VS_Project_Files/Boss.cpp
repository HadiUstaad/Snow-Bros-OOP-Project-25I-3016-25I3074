#include "Boss.h"


Boss::Boss(float x, float y, float w, float h, int maxHp, int score)
    : Enemies(x, y, w, h, maxHp, 10, score)  
{
    maxHealth = maxHp;          
    currentPhase = 1;           
    phaseTimer = 0;          
    canSpawnChild = true;     
}


void Boss::takeDamage(int damage)
{
    
    health -= damage;
    if (health <= 0)
    {
        health = 0;
        // onDeath();
    }


    float healthPercentage = 100*getHealth()/maxHealth;

    // change to phase 2 at 1/3 of taken damage
    if (healthPercentage <= 66 && currentPhase == 1)
    {
        currentPhase = 2;
        phaseTimer = 0;      
    }
    // Transition to phase 3 at 33 percent health
    else if (healthPercentage <= 33 && currentPhase == 2)
    {
        currentPhase = 3;
        phaseTimer = 0;      
    }
}


int Boss::getCurrentPhase()
{
    return currentPhase;
}


int Boss::getHealth()
{
    return health;
}

float Boss::getPhaseTimer()
{
    return phaseTimer;
}
bool Boss::getCanSpawnChild()
{
    return canSpawnChild;
}

void Boss::setCurrentPhase(int phase)
{
    currentPhase = phase;
}
void Boss::setHealth(int health)
{
    this->health = health;
}
void Boss::setPhaseTimer(float time)
{
    phaseTimer = time;
}
void Boss::setCanSpawnChild(bool spawn)
{
    canSpawnChild = spawn;
}

void Boss::drawHitbox(sf::RenderWindow& window)
{
    // same as base class
    Enemies::drawHitbox(window);
}

void Boss::updateMovement(float deltaTime, platform platform[], int count)
{
   //Enemies::updateMovement(deltaTime,platform,count);
    updateHitboxPosition();
}