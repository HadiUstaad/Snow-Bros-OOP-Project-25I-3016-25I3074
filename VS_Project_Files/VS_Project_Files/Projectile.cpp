#include "Projectile.h"

// x y are position in space. vx vy velocities
Projectile::Projectile(float x, float y, float vx, float vy, int dmg)
    : GameObject(x, y, true, 10, 10)  // projectiles are small 10x10
{
    velocityX = vx;         // horizontal speed
    velocityY = vy;         // vertical speed
    damageAmount = dmg;     // damage to player
    hasHitTarget = false;   // hasnt hit anything yet
}


Projectile::~Projectile()
{
   
}


void Projectile::updatePosition(float deltaTime)
{
    // if something hit already stop moving
    if (hasHitTarget)
    {
        return;
    }

    float newX = getX() + (velocityX * deltaTime);
    float newY = getY() + (velocityY * deltaTime);


    setPosition(newX, newY);

    // Deactivate if it goes offscreen
    if (newX < -50 || newX > 850 || newY < -50 || newY > 650)
    {
        setActive(false);
    }
}

// deactivates the object
void Projectile::markAsHit()
{
    hasHitTarget = true;
    setActive(false);      
}

bool Projectile::hasHit()
{
    return hasHitTarget;
}

int Projectile::getDamage()
{
    return damageAmount;
}

float Projectile::getVelocityX()
{
    return velocityX;
}

float Projectile::getVelocityY()
{
    return velocityY;
}