#include "Fooga.h"
#include "Platform.h"
#include <ctime>
#include<iostream>
using namespace std;


static const float ENEMY_FRAME_X = 432;
static const float ENEMY_FRAME_Y = 24;
static const float ENEMY_FRAME_WIDTH = 135;
static const float ENEMY_FRAME_HEIGHT = 158;


static const float SNOWBALL_FRAME_X = 262;
static const float SNOWBALL_FRAME_Y = 885;
static const float SNOWBALL_FRAME_WIDTH = 67;
static const float SNOWBALL_FRAME_HEIGHT = 81;
Fooga::Fooga(float x, float y) : FlyEnemy(x, y, 50, 50, 4, 60, 150),
texture(), sprite(texture), snowball()
{
    isFlying = true; // starts in air
    landTimer = 7; // will attempt landing after 3 seconds
    alive = true;
    froze = false;

    hoverHeight = y - 100;

    setSpeed(150);
    shape.setSize(sf::Vector2f(getWidth(), getHeight()));
    shape.setFillColor(sf::Color::Transparent);    
    shape.setPosition(sf::Vector2f(getX(), getY()));

    if (!snowball.loadFromFile("SnowBrosAssets/Images/Player_Red.png"))
    {
        cout << "snowball texture failed to load\n";
        shape.setFillColor(sf::Color::Yellow);
    }
    else
    {
        cout << "snowball texture loaded\n";
    }

    if (!texture.loadFromFile("SnowBrosAssets/Images/FlyingFoogaFoog_Red.png"))
    {
        cout << "FOOGA texture failed to load\n";
        shape.setFillColor(sf::Color::Yellow);
    }
    else {
        cout << "Fooga texture loaded\n";
    }


    frameRect = sf::IntRect(sf::Vector2i(ENEMY_FRAME_X, ENEMY_FRAME_Y),
        sf::Vector2i(ENEMY_FRAME_WIDTH, ENEMY_FRAME_HEIGHT));

    sprite = sf::Sprite(texture, frameRect);


    float scaleX = getWidth() / ENEMY_FRAME_WIDTH;
    float scaleY = getHeight() / ENEMY_FRAME_HEIGHT;
    sprite.setScale({ scaleX, scaleY });
    sprite.setPosition(sf::Vector2f(getX(), getY()));
}


void Fooga::updateMovement(float deltaTime, platform platforms[], int count)
{
    
    if (froze)
    {
        updateHitboxPosition();
        applygravity(deltaTime, platforms, count);
        float scaleX = getWidth() / SNOWBALL_FRAME_WIDTH;
        float scaleY = getHeight() / SNOWBALL_FRAME_HEIGHT;
        sprite.setScale({ scaleX, scaleY });
        sprite.setPosition(sf::Vector2f(getX(), getY()));
        
        return;
    }

    // decrease timer until it will be 0
    landTimer -= deltaTime;

    // if flying update hover motion  else apply gravity logic
    if (isFlying)
    {
       
        hoverTimer += deltaTime;

        float amplitude = 120.0f;   // height of movement
        float speed = 3.0f;        // speed of oscillation

        float newY = hoverHeight + amplitude * sin(hoverTimer * speed);
        float minY = 50.0f;     // top limit (adjust if needed)
        float maxY = 550.0f;    // ground level (important)

        // clamp
        if (newY < minY) newY = minY;
        if (newY > maxY) newY = maxY;

      
        float newX = getX() + (moveDirection * getSpeed() * deltaTime);

        // screen boundaries
        if (newX <= 0 || newX >= 800 - getWidth())
        {
            moveDirection *= -1; // reverse direction
            newX = getX() + (moveDirection * getSpeed() * deltaTime);
        }

        setPosition(newX, newY);

        // check if time to land
        if (landTimer <= 0)
        {
            attemptLanding();
            landTimer = 7;   // stay grounded for 2 seconds
        }
    }
    else
    {
        applygravity(deltaTime, platforms, count);
        // On ground just move horizontally
        float newX = getX() + (getSpeed() * deltaTime);

        // Reverse at edges
        if (newX <= 0 || newX >= 800 - getWidth())
        {
            setSpeed(-getSpeed());
            newX = getX() + (getSpeed() * deltaTime);
        }

        setPosition(newX, getY());

        // Check if time to takeoff
        if (landTimer <= 0)
        {
            takeoff();
            landTimer = 7;   
        }
    }

    float scaleX = getWidth() / ENEMY_FRAME_WIDTH;
    float scaleY = getHeight() / ENEMY_FRAME_HEIGHT;
    if (moveDirection == 1)
    {
        sprite.setScale({ -scaleX, scaleY });
        sprite.setPosition(sf::Vector2f(getX() + getWidth(), getY()));
    }
    else
    {
        sprite.setScale({ scaleX, scaleY });
        sprite.setPosition(sf::Vector2f(getX(), getY()));
    }
    shape.setPosition(sf::Vector2f(getX(), getY()));
    updateHitboxPosition();
}

void Fooga::drawHitbox(sf::RenderWindow& window)
{
    
    if (alive && getActive())
    {
        window.draw(hitbox);
    }
}


void Fooga::draw(sf::RenderWindow& window)
{
    if (getActive())
    {
        window.draw(sprite);
    }
}

// attempts to land on nearest platform below
void Fooga::attemptLanding()
{
    
    isFlying = false;
}

// Takes off from ground back into air
void Fooga::takeoff()
{
    isFlying = true;
    hoverHeight = getY()-120;   // set new hover center at current height
}

void Fooga::applygravity(float deltaTime, platform platforms[], int count)
{

    if (!isFlying)
    {

        if (!isGrounded)
        {
            float max_velocity = 2500;
            float gravity = 1000;
            velocityY += gravity * deltaTime ; //changed here
            if (velocityY > max_velocity)
            {
                velocityY = max_velocity;
            }
        }

        float newY = getY() + velocityY * deltaTime;
        setPosition(getX(), newY);

        //  check landing on any platform
        isGrounded = false;

        float ex = getX();          // enemy x starting point
        float ey = getY();          // enemy y starting point (in sfml +y axis is downwards)
        float ew = getWidth();      // x + ew will give the position of ending horizontal of enemy
        float eh = getHeight();

        for (int i = 0; i < count; i++)
        {
            // stores position and size of each platform one by one
            sf::Vector2f pPos = platforms[i].getBody().getPosition();
            sf::Vector2f pSize = platforms[i].getBody().getSize();

            // horizontal overlap of enmey with platform
            bool overlapX = (ex + ew > pPos.x) && (ex < pPos.x + pSize.x);
            if (!overlapX)
            {
                continue;
            }

            // check if enemy bottom crossed the platforms top
            float enemyBottom = ey + eh;
            float prevBottom = enemyBottom - velocityY * deltaTime;   // where bottom was

            // it chec
            bool crossedTop = (prevBottom <= pPos.y + 2.0f) && (enemyBottom >= pPos.y);

            if (crossedTop)
            {
                // snap enemy to platform surface so perfectly aligned
                setPosition(getX(), pPos.y - eh);
                velocityY = 0;
                isGrounded = true;
                break;
            }
        }

        //flip
        if (getX() < 0 || getX() > 800 - getWidth())
        {
            moveDirection *= 1;
        }

        float scaleX = getWidth() / ENEMY_FRAME_WIDTH;
        float scaleY = getHeight() / ENEMY_FRAME_HEIGHT;
        if (moveDirection == 1)
        {
            sprite.setScale({ -scaleX, scaleY });
            sprite.setPosition(sf::Vector2f(getX() + getWidth(), getY()));
        }
        else
        {
            sprite.setScale({ scaleX, scaleY });
            sprite.setPosition(sf::Vector2f(getX(), getY()));
        }

    }
    
}

void Fooga::freeze() {

    froze = true;
    isFlying = false;

    frameRect = sf::IntRect(sf::Vector2i(SNOWBALL_FRAME_X, SNOWBALL_FRAME_Y),
        sf::Vector2i(SNOWBALL_FRAME_WIDTH, SNOWBALL_FRAME_HEIGHT));
    sprite = sf::Sprite(snowball, frameRect);
}

bool Fooga::checkfreeze() {
    return froze;
}


void Fooga::onHit()
{
    if (!froze) {
        freeze();
    }
    else {
        alive = false;
        setActive(false);
    }
}

bool Fooga::isAlive()
{
    return alive;
}

sf::FloatRect Fooga::getBounds() {
    return sprite.getGlobalBounds();
}