#include "Mogera.h"
#include <iostream>
using namespace std;

static const float ENEMY_FRAME_X = 176;
static const float ENEMY_FRAME_Y = 2;
static const float ENEMY_FRAME_WIDTH = 163;
static const float ENEMY_FRAME_HEIGHT = 203;


static const float SNOWBALL_FRAME_X = 293;
static const float SNOWBALL_FRAME_Y = 390;
static const float SNOWBALL_FRAME_WIDTH = 236;
static const float SNOWBALL_FRAME_HEIGHT = 103;


Mogera::Mogera(float x, float y) : Boss(x, y, 200, 200, 30, 1000)
, texture(), sprite(texture), snowball()
{
    childCount = 0;           
    maxChildPerPhase = 4;        
    spawnTimer = 4;             

    
    shape.setSize(sf::Vector2f(getWidth(), getHeight()));
    shape.setFillColor(sf::Color::Transparent);         
    shape.setPosition(sf::Vector2f(getX(), getY()));
    if (!snowball.loadFromFile("SnowBrosAssets/Images/Mogera.png"))
    {
        cout << "snowball texture failed to load\n";
        shape.setFillColor(sf::Color::Yellow);
    }
    else
    {
        cout << "snowball texture loaded\n";
    }

    if (!texture.loadFromFile("SnowBrosAssets/Images/Mogera.png"))
    {
        cout << "Mogera texture failed to load\n";
        shape.setFillColor(sf::Color::Yellow);
    }
    else {
        cout << "Mogera texture loaded\n";
    }


    frameRect = sf::IntRect(sf::Vector2i(ENEMY_FRAME_X, ENEMY_FRAME_Y),
        sf::Vector2i(ENEMY_FRAME_WIDTH, ENEMY_FRAME_HEIGHT));

    sprite = sf::Sprite(texture, frameRect);


    float scaleX = getWidth() / ENEMY_FRAME_WIDTH;
    float scaleY = getHeight() / ENEMY_FRAME_HEIGHT;
    sprite.setScale({ scaleX, scaleY });
    sprite.setPosition(sf::Vector2f(getX(), getY()));
}

void Mogera::updateMovement(float deltaTime, platform platform[], int count)
{
    if (!alive)
    {
        frameRect = sf::IntRect(sf::Vector2i(SNOWBALL_FRAME_X, SNOWBALL_FRAME_Y),
            sf::Vector2i(SNOWBALL_FRAME_WIDTH, SNOWBALL_FRAME_HEIGHT));
        sprite = sf::Sprite(snowball, frameRect);
        float scaleX = getWidth() / SNOWBALL_FRAME_WIDTH;
        float scaleY = getHeight() / SNOWBALL_FRAME_HEIGHT;
        sprite.setScale({ scaleX, scaleY });
        
        sprite.setPosition(sf::Vector2f(getX(), getY()));
        updateHitboxPosition();
        return;
    }
}


void Mogera::updatePhase(float deltaTime)
{
    

    setPhaseTimer(getPhaseTimer() + deltaTime * 100) ;

    // only count down if not already waiting to spawn
    // this prevents the bool from getting reset before Game.cpp 
    //can actually spawn the enmemy
    if(!getCanSpawnChild())
    {
        spawnTimer -= deltaTime * 100;
    }

    // Different behavior in different phase
    if (getCurrentPhase() == 1)
    {
        // child should spawn if timer is 0 and number of child are less than max child
        if (spawnTimer <= 0 && (childCount < maxChildPerPhase))
        {
            spawnMinions();
            spawnTimer = 400;     
           
        }
    }
    else if (getCurrentPhase() == 2)
    {
       
        if (spawnTimer <= 0 && (childCount < maxChildPerPhase))
        {
            spawnMinions();
            spawnTimer = 250;   
        }
    }
    else if (getCurrentPhase() == 3)
    {
        
        if (spawnTimer <= 0 && (childCount < maxChildPerPhase))
        {
            spawnMinions();
            spawnTimer = 150;     
        }
    }
}




void Mogera::spawnMinions()
{
    setCanSpawnChild(true);
}


void Mogera::draw(sf::RenderWindow& window)
{
    if (getActive())
    {
    }
        window.draw(sprite);
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
    // mogera takes damage from snowballs
    takeDamage(5);     // each snowball hit does 5 damage. needs 6 hits to kill (30hp)

    if (getHealth() <= 0)
    {
        alive = false;
        setActive(false);
        return;
    }

    
    if (getCurrentPhase() == 2)
    {
        sprite.setColor(sf::Color(180, 180, 255)); 
    }
    else if (getCurrentPhase() == 3)
    {
        sprite.setColor(sf::Color(255, 100, 100)); 
    }
}