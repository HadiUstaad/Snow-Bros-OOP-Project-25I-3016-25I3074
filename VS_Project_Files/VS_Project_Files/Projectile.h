#pragma once
#pragma once
#include "GameObjects.h"

using namespace std;


class Projectile : public GameObject
{
protected:
    float velocityX;        
    float velocityY;        
    int damageAmount;       // damage dealt to player on hit
    bool hasHitTarget;      // has projectile hit something

public:
   
    Projectile(float x, float y, float vx, float vy, int dmg);

    virtual ~Projectile();

    virtual void updatePosition(float deltaTime);

   
    void markAsHit();               // deactivate object
    bool hasHit();                  // check if already hit
    int getDamage();                // get damage value
    float getVelocityX();
    float getVelocityY();
};