#pragma once
#include "Enemy.h"
#include "Platform.h"

using namespace std;

class Boss : public Enemies
{
private:
    int maxHealth;              
    int currentPhase;           // which attack phase 1, 2, 3. boss has attack phases
    float phaseTimer;           // time in current phase
    bool canSpawnChild;       

public:
    
    Boss(float x, float y, float w, float h, int maxHp, int score);

    virtual ~Boss() = default;

    // each boss has unique phases so pure virtual
    virtual void updatePhase(float deltaTime) = 0;

    // pure virtual as each boss spawns different minions and some do not
    virtual void spawnMinions() = 0;

    virtual void updateMovement(float deltaTime, platform platform[], int count);

    virtual void draw(sf::RenderWindow& window) = 0;


    void takeDamage(int damage);        // this can change the phases

    int getCurrentPhase();              // get current phase number
    int getHealth();           
    float getPhaseTimer();
    bool getCanSpawnChild();

    void setCurrentPhase(int phase); 
    void setHealth(int health);           
    void setPhaseTimer(float time);
    void setCanSpawnChild(bool spawn);


};