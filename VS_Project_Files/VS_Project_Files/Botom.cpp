#include "Botom.h"
#include "Ball.h"
#include <iostream>
#include <ctime>

using namespace std;
//Modify add texture

static const float BOTON_FRAME_X = 11;   
static const float BOTON_FRAME_Y = 136;
static const float BOTON_FRAME_WIDTH = 81;
static const float BOTON_FRAME_HEIGHT = 84;


static const float SNOWBALL_FRAME_X = 262;
static const float SNOWBALL_FRAME_Y =885;
static const float SNOWBALL_FRAME_WIDTH = 67;
static const float SNOWBALL_FRAME_HEIGHT = 81;

Boton::Boton(float x, float y) : GroundEnemy(x, y, 50, 50, 300, 50, 100)
, texture(), sprite(texture),snowball()
{

    froze = false;
    alive = true;
    moveDirection = 1;

    movespeed = 150;


    shape.setSize(sf::Vector2f(getWidth(), getHeight()));
    shape.setFillColor(sf::Color::Transparent); // transparent so dont show
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

    if (!texture.loadFromFile("SnowBrosAssets/Images/Botom_Pink.png")) 
    {
        cout << "Boton texture failed to load\n";
        shape.setFillColor(sf::Color::Yellow);
    }
    else {
        cout << "Boton texture loaded\n";
    }

    
    frameRect = sf::IntRect(sf::Vector2i(BOTON_FRAME_X, BOTON_FRAME_Y),
        sf::Vector2i(BOTON_FRAME_WIDTH, BOTON_FRAME_HEIGHT)
    );

    sprite = sf::Sprite(texture, frameRect);

    
    float scaleX = getWidth() / BOTON_FRAME_WIDTH;
    float scaleY = getHeight() / BOTON_FRAME_HEIGHT;
    sprite.setScale({ scaleX, scaleY });
    sprite.setPosition(sf::Vector2f(getX(), getY()));
}

void Boton::updateMovement(float deltaTime, platform platforms[], int count)
{

    if (getSnowball() || froze || !alive)
    {
        float scaleX = getWidth() / SNOWBALL_FRAME_WIDTH;
        float scaleY = getHeight() / SNOWBALL_FRAME_HEIGHT;
        sprite.setScale({ scaleX, scaleY });
        sprite.setPosition(sf::Vector2f(getX(), getY()));
        
        return;
    }


  
    // checks if it is in air and then pulls it down until it reaches a ground
    applyGravity(deltaTime, platforms, count);

    // walks horizontally on ground. no vertical movement
    if (isGrounded)
    {
        float newX = getX() + (moveDirection * getSpeed() * deltaTime);

        // screen boundary reversal check
        if (newX <= 0 || newX >= 800 - getWidth())
        {
            moveDirection *= -1;
            newX = getX() + (moveDirection * getSpeed() * deltaTime);
        }

        // checks that if it is at edge. it creates a variable probe which stores 1 pixel left position
        // ahead of boton. if that place has air it will either fal or reverse direction
        // if it is grounded it will keep moving in its direcetion

        float probeY = getY() + getHeight() + 1.0f;   // one pixel below feet
        float probeX;
        if (moveDirection > 0)
        {
            probeX = newX + getWidth();
        }
        else
        {
            probeX = newX - 1;
        }

        bool groundAhead = false;
        for (int i = 0; i < count; i++)
        {
            sf::Vector2f pPos = platforms[i].getBody().getPosition();
            sf::Vector2f pSize = platforms[i].getBody().getSize();

           
            bool inX = (probeX >= pPos.x && probeX <= pPos.x + pSize.x);
            bool inY = (probeY >= pPos.y && probeY <= pPos.y + pSize.y);
           
            if (inX && inY)
            {
                groundAhead = true;
                break;
            }
        }

        if (groundAhead)
        {
            setPosition(newX, getY());
        }
        else
        {
            
            
            setPosition(newX, getY());
            isGrounded = false;   // important
            
        }

    }
   
    
    sprite.setPosition(sf::Vector2f(getX(), getY()));

    // flip
    float scaleX = getWidth() /BOTON_FRAME_WIDTH;
    float scaleY = getHeight() / BOTON_FRAME_HEIGHT;
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
    // makes hitbox at the same positon as sprite
    updateHitboxPosition();
}



sf::FloatRect Boton::getBounds() {
    return sprite.getGlobalBounds();
}


//freezing functions

void Boton::freeze() {

    froze = true;
    
    frameRect= sf::IntRect(sf::Vector2i(SNOWBALL_FRAME_X, SNOWBALL_FRAME_Y),
        sf::Vector2i(SNOWBALL_FRAME_WIDTH, SNOWBALL_FRAME_HEIGHT));
    sprite = sf::Sprite(snowball, frameRect);

}

bool Boton::checkfreeze() {
    return froze;
}


//Eliminating functions
void Boton::onHit() {

    if (!froze) {
        freeze();
    }
    else {
        alive = false;
        setActive(false);
    }
}

bool Boton::isAlive() {
    return alive;
}

void Boton::draw(sf::RenderWindow& window)
{
    if (alive && getActive())
    {
        window.draw(sprite);
    }
}

// modify to solve hitbox error
void Boton::drawHitbox(sf::RenderWindow& window)
{
    // only draws hitbox when enemy is alive and active
    // this prevents the bug when hitbox was remaining after object destroyed
    if (alive && getActive())
    {
        window.draw(hitbox);
    }
}

