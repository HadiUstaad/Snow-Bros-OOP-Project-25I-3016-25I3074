#include "Gamakichi.h"
#include <cmath>
#include <iostream>

using namespace std;


static const float ENEMY_FRAME_X = 1446;
static const float ENEMY_FRAME_Y = 16;
static const float ENEMY_FRAME_WIDTH = 1087;
static const float ENEMY_FRAME_HEIGHT = 623;

Gamakichi::Gamakichi(float x, float y)
    : Boss(x, y, 250, 100, 60, 10000)   // big 120x100, 60 hp, 10000 score
 , texture(), sprite(texture)
{
    rocketCount = 0;
    fireTimer = 3;          // first shot after 3 seconds
    fireCooldown = 3;

    childCount = 0;
    spawnTimer = 10;
    spawnCooldown = 10;

    lastPlayerX = 300;  // random value. will be updated during gameplay
    lastPlayerY = 300;

    alive = true;

    // set all rocket slots to null
    for (int i = 0; i < 8; i++)
    {
        rockets[i] = nullptr;
    }

    shape.setSize(sf::Vector2f(getWidth(), getHeight()));
    shape.setFillColor(sf::Color::Transparent);     
    shape.setPosition(sf::Vector2f(getX(), getY()));

    if (!texture.loadFromFile("SnowBrosAssets/Images/Gamakichi.png"))
    {
        cout << "Gamakichi texture failed to load\n";
        shape.setFillColor(sf::Color::Yellow);
    }
    else {
        cout << "Gamakichi texture loaded\n";
    }


    frameRect = sf::IntRect(sf::Vector2i(ENEMY_FRAME_X, ENEMY_FRAME_Y),
        sf::Vector2i(ENEMY_FRAME_WIDTH, ENEMY_FRAME_HEIGHT));

    sprite = sf::Sprite(texture, frameRect);


    float scaleX = getWidth() / ENEMY_FRAME_WIDTH;
    float scaleY = getHeight() / ENEMY_FRAME_HEIGHT;
    sprite.setScale({ scaleX, scaleY });
    sprite.setPosition(sf::Vector2f(getX(), getY()));

}


Gamakichi::~Gamakichi()
{
    
    for (int i = 0; i < 8; i++)
    {
        if (rockets[i] != nullptr)
        {
            delete rockets[i];
            rockets[i] = nullptr;
        }
    }
}


void Gamakichi::updatePhase(float deltaTime)
{
    if (!alive)
    {
        return;
    }

    // update the time in the current phase
    setPhaseTimer(getPhaseTimer() + deltaTime * 100);

    // count down fire timer
    fireTimer -= deltaTime * 150;
    spawnTimer -= deltaTime * 100;

    

    if (spawnTimer <= 0)
    {
        spawnMinions();
        spawnTimer = spawnCooldown;
    }

    // update all rockets
    for (int i = 0; i < 8; i++)
    {
        if (rockets[i] != nullptr && rockets[i]->getActive())
        {
            rockets[i]->updatePosition(deltaTime);
        }
    }
    if (fireTimer <= 0)
    {
        fireRockets(lastPlayerX, lastPlayerY);

        // phase 2 and 3 fire faster
        if (getCurrentPhase() == 1)
        {
            fireCooldown = 3;
        }
        else if (getCurrentPhase() == 2)
        {
            fireCooldown = 2;
        }
        else
        {
            fireCooldown = 1.2f;
        }

        fireTimer = fireCooldown;
    }
}


void Gamakichi::fireRockets(float playerX, float playerY)
{
    // x+ width/2 gives middle x of rocket
    float midx = getX() + getWidth() / 2;
    float midy = getY() + getHeight() / 2;
    float dx = playerX - midx;
    float dy = playerY - midy;
    float dist = sqrt(dx * dx + dy * dy);

    // this is to atleast give space to rocket
    // iske baghair rocket and player aapas mei glitch kar rahay thay
    if (dist < 1)
    {
        dist = 1;
    }

    float speed = 120;  

    // we multupy speed into unit vector
    float nx = (dx / dist) * speed;
    float ny = (dy / dist) * speed;

    // phase 1: one rocket at player
    // phase 2: three rockets spread
    // phase 3: five rockets full spread
    int shots;
    if (getCurrentPhase() == 1)
    {
        shots = 2;
    }
    if (getCurrentPhase() == 2)
    {
        shots = 4;
    }
    if (getCurrentPhase() == 3) 
    {
        shots = 6;
    }

    float spreadAngle = 20;   // each rocket will fire in diff direction.
    // this will tell angle between 2 jo saath saath hai

    for (int s = 0; s < shots; s++)
    {
       // modify can modify the loop logic a little bit
        int slot = -1;  // -1 no empty slot. 
        for (int i = 0; i < 8; i++)
        {
            if (rockets[i] == nullptr || !rockets[i]->getActive())
            {
                slot = i;
                break;
            }
        }

        if (slot == -1)
        {
            break;  // no slot available
        }

        // calculate angle offset for spread
        
        // modify rocket spawn from above
        float angleOffset = (s - shots / 2) * spreadAngle;

        float rad = angleOffset * (3.14f / 180); // computer doesnot know degrees but radians

        // rotate the velocity by angle
        float rotVx = nx * cos(rad) - ny * sin(rad);
        float rotVy = nx * sin(rad) + ny * cos(rad);

        // delete old rocket in this slot if it exists
        if (rockets[slot] != nullptr)
        {
            delete rockets[slot];
        }

        
                                                                
        rockets[slot] = new GamakichiRocket(midx, midy, rotVx, rotVy);  //vx cy are velocity
        rocketCount = slot + 1;
    }
}


void Gamakichi::spawnMinions()
{
    childCount++;
    setCanSpawnChild(true);
}


void Gamakichi::updateMovement(float deltaTime, platform platform[], int count)
{
    // movement added later
    if (!alive)
    {
        return;
    }

    updateHitboxPosition();
}


void Gamakichi::draw(sf::RenderWindow& window)
{
    if (!alive || !getActive())
    {
        return;
    }

    window.draw(sprite);

    // draw all active rockets
    for (int i = 0; i < 8; i++)
    {
        if (rockets[i] != nullptr)  
        {
            if (rockets[i]->getActive())
            {
                rockets[i]->draw(window);
            }
        }
    }
}


void Gamakichi::drawHitbox(sf::RenderWindow& window)
{
    if (alive && getActive())
    {
        window.draw(hitbox);
    }
}


GamakichiRocket** Gamakichi::getRockets()
{
    return rockets; // rockets is an array and we are returnig a pointer which points to a pointer
}


int Gamakichi::getRocketCount()
{
    return 8;   // we have 8 rockets
}


void Gamakichi::onHit()
{
    // bosses use takeDamage not onHit for their HP. this is called by snowball
    takeDamage(1);

    if (getHealth() <= 0)
    {
        alive = false;
        setActive(false);
    }

    // damage changing will be here
    if (getCurrentPhase() == 2)
    {
        shape.setFillColor(sf::Color(0, 120, 0));   // darker green
    }
    else if (getCurrentPhase() == 3)
    {
        shape.setFillColor(sf::Color(0, 80, 0));    // very dark
    }
}


bool Gamakichi::isAlive()
{
    return alive;
}