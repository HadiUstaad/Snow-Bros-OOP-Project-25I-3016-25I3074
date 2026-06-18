#include "Mogera_child.h"
#include <iostream>
using namespace std;

static const float ENEMY_FRAME_X = 40;
static const float ENEMY_FRAME_Y = 195;
static const float ENEMY_FRAME_WIDTH = 56;
static const float ENEMY_FRAME_HEIGHT = 59;

MogeraChild::MogeraChild(float x, float y, int direction)
    : GroundEnemy(x, y, 50, 50, 1, 80, 50)   // small 25x25, 1 hp, fast, 50 score
    , texture(), sprite(texture)
{
    moveDirection = direction;  // direction passed by Mogera when spawning
    alive = true;
    froze = false;

    shape.setSize(sf::Vector2f(getWidth(), getHeight()));
    shape.setFillColor(sf::Color::Transparent);     // purple color to show its a child of boss
    shape.setPosition(sf::Vector2f(getX(), getY()));

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



void MogeraChild::updateMovement(float deltaTime, platform platforms[], int count)
{
    if (getSnowball())
    {
        return;
    }

    if (froze)
    {
        return;
    }

    if (!alive)
    {
        return;
    }

    // apply gravity so child falls onto platforms
    applyGravity(deltaTime, platforms, count);

    if (isGrounded)
    {
        // just keep walking in one direction. no reversal. falls off edges
        float newX = getX() + (moveDirection * getSpeed() * deltaTime);

        // deactivate if it walks off screen
        if ((newX <= -5 || newX >= 805 - getWidth()) && getY()-getHeight() >=400)
        {
            alive = false;
            setActive(false);
            return;
        }
        else if ((newX <= 0 || newX >= 800)&&getY() - getHeight() <= 500)
        {
            moveDirection *= -1;
            newX = getX() + (moveDirection * getSpeed() * deltaTime);
        }

        setPosition(newX, getY());
    }

    sprite.setPosition(sf::Vector2f(getX(), getY()));
    updateHitboxPosition();
}


void MogeraChild::draw(sf::RenderWindow& window)
{
    if (alive && getActive())
    {
        window.draw(sprite);
    }
}


void MogeraChild::drawHitbox(sf::RenderWindow& window)
{
    if (alive && getActive())
    {
        window.draw(hitbox);
    }
}


sf::FloatRect MogeraChild::getBounds()
{
    return sprite.getGlobalBounds();
}


void MogeraChild::freeze()
{
    froze = true;
    shape.setFillColor(sf::Color::Cyan);
}


bool MogeraChild::checkfreeze()
{
    return froze;
}


void MogeraChild::onHit()
{
    // child dies in one hit since hp is 1. no freeze phase needed
    alive = false;
    setActive(false);
}


bool MogeraChild::isAlive()
{
    return alive;
}