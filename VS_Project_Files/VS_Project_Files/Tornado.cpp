#include "Tornado.h"
#include <iostream>
using namespace std;
static const float ENEMY_FRAME_X = 20;
static const float ENEMY_FRAME_Y = 41;
static const float ENEMY_FRAME_WIDTH = 98;
static const float ENEMY_FRAME_HEIGHT = 114;


static const float SNOWBALL_FRAME_X = 262;
static const float SNOWBALL_FRAME_Y = 885;
static const float SNOWBALL_FRAME_WIDTH = 67;
static const float SNOWBALL_FRAME_HEIGHT = 81;

Tornado::Tornado(float x, float y) : FlyEnemy(x, y, 45, 45, 5, 70, 200),
texture(), sprite(texture), snowball()
{
    throwTimer = 1;          
    throwCooldown = 12;       
    froze = false;
    alive = true;

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

    if (!texture.loadFromFile("SnowBrosAssets/Images/Tornado_Red.png"))
    {
        cout << "Tornado texture failed to load\n";
        shape.setFillColor(sf::Color::Yellow);
    }
    else {
        cout << "Tornado texture loaded\n";
    }


    frameRect = sf::IntRect(sf::Vector2i(ENEMY_FRAME_X, ENEMY_FRAME_Y),
        sf::Vector2i(ENEMY_FRAME_WIDTH, ENEMY_FRAME_HEIGHT));

    sprite = sf::Sprite(texture, frameRect);


    float scaleX = getWidth() / ENEMY_FRAME_WIDTH;
    float scaleY = getHeight() / ENEMY_FRAME_HEIGHT;
    sprite.setScale({ scaleX, scaleY });
    sprite.setPosition(sf::Vector2f(getX(), getY()));
}


void Tornado::updateMovement(float deltaTime, platform platforms[], int count)
{
    // If snowballed dont move or throw
    if (getSnowball() || froze)
    {
        updateHitboxPosition();
        applygravity(deltaTime, platforms, count);
        float scaleX = getWidth() / SNOWBALL_FRAME_WIDTH;
        float scaleY = getHeight() / SNOWBALL_FRAME_HEIGHT;
        sprite.setScale({ scaleX, scaleY });
        sprite.setPosition(sf::Vector2f(getX(), getY()));
        return;
    }


    if (!alive)
    {
        return;
    }

    // flying movement is same as flying enemy
    FlyEnemy::updateMovement(deltaTime, platforms, count);

    throwTimer -= deltaTime *10;

    sprite.setPosition(sf::Vector2f(getX(), getY()));
    updateHitboxPosition();
}


bool Tornado::canThrow()
{
    // throws if not snowballed and it is time to throw
    //modify player in range check
   //if () 
    {
        if (throwTimer <= 0 && !getSnowball())
        {
            throwTimer = throwCooldown;     // reset timer
            return true;
        }
    }
    return false;
}


Knife* Tornado::createKnife(float playerX, float playerY)
{
    // Create knife at tornado position aimed at player
    float midx = getX() + (getWidth() / 2);
    float midy = getY() + (getHeight() / 2);
    return new Knife(midx,midy, playerX, playerY);
}


void Tornado::draw(sf::RenderWindow& window)
{
    if (getActive())
    {
        window.draw(sprite);
    }
}

void Tornado::drawHitbox(sf::RenderWindow& window)
{
    
    if (alive && getActive())
    {
        window.draw(hitbox);
    }
}

bool Tornado::isAlive()
{
    return alive;
}

void Tornado::onHit() {

    if (!froze) {
        freeze();
    }
    else {
        alive = false;
        setActive(false);
    }
}

void Tornado::freeze() 
{

    froze = true;
    frameRect = sf::IntRect(sf::Vector2i(SNOWBALL_FRAME_X, SNOWBALL_FRAME_Y),
        sf::Vector2i(SNOWBALL_FRAME_WIDTH, SNOWBALL_FRAME_HEIGHT));
    sprite = sf::Sprite(snowball, frameRect);
}

bool Tornado::checkfreeze() {
    return froze;
}


void Tornado::applygravity(float deltaTime, platform platforms[], int count)
{

   

        if (!isGrounded)
        {
            float max_velocity = 2500;
            float gravity = 1000;
            velocityY += gravity * deltaTime; //changed here
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