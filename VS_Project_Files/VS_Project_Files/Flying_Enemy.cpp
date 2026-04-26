#include "Flying_Enemy.h"
#include <cmath>



FlyEnemy::FlyEnemy(float x, float y, float w, float h, int hp, int speed, int score)
    : Enemies(x, y, w, h, hp, speed, score)
{
    amplitude = 80;      // moves 30 pixels up and down
    frequency = 0.005f;       // completes 2 oscillations per second
    timeCounter = 0;     // starts at 0 time
    hoverHeight = y;        // the starting y value is the center of oscillation
}

// Updates position using sine wave for up down motion
void FlyEnemy::updateMovement(float deltaTime, platform platforms[], int count)
{
    // If snowballed stop all movement
    if (getSnowball())
        return;

    // Update hover motion up and down 
    // Increment time counter
    timeCounter += deltaTime * 100;

    // Calculate Y offset using sine function sin returns value between -1 and 1
    // multiply by amplitude to get actual pixel offset
    float offset = amplitude * sin(frequency * timeCounter);

    // move horizontally at constant speed
    float newX = getX() + (getSpeed() * deltaTime);

    // reverse direction at screen edges. X will work normally as ground enemy. y will be different
    if (newX <= 0 || newX >= 800 - getWidth())
    {
        // se speed to move in opposite direction
        setSpeed(getSpeed() * -1);
        newX = getX() + (getSpeed() * deltaTime);
    }

    // Apply new position of X,  Y is updated by adding offset into the fixed initial (hoverheight)
    setPosition(newX, hoverHeight + offset);
}


