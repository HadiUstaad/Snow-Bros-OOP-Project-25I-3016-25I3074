#include "Platform.h"
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;

static const float ENEMY_FRAME_X = 21;
static const float ENEMY_FRAME_Y = 143;
static const float ENEMY_FRAME_WIDTH = 687;
static const float ENEMY_FRAME_HEIGHT = 115;

platform::platform() : texture(), sprite(texture)
{
    body.setSize({ 0, 0 });
    posX = 0;
    posY = 0;
    width = 0;
    height = 0;
}

platform::platform(float x, float y, float width, float height) : texture(), sprite(texture)
{
    body.setSize({ width, height });
    body.setPosition({ x, y });
    body.setFillColor(sf::Color::Transparent);

    posX = x;
    posY = y;
    this->width = width;
    this->height = height;

    if (!texture.loadFromFile("SnowBrosAssets/Images/Platform.png"))
    {
        cout << "Platform texture failed to load\n";
    }
    else
    {
        cout << "Platform texture loaded\n";
    }

    frameRect = sf::IntRect(
        sf::Vector2i((int)ENEMY_FRAME_X, (int)ENEMY_FRAME_Y),
        sf::Vector2i((int)ENEMY_FRAME_WIDTH, (int)ENEMY_FRAME_HEIGHT)
    );

    sprite = sf::Sprite(texture, frameRect);

    float scaleX = getWidth() / ENEMY_FRAME_WIDTH;
    float scaleY = getHeight() / ENEMY_FRAME_HEIGHT;
    sprite.setScale({ scaleX, scaleY });
    sprite.setPosition(sf::Vector2f(getX(), getY()));
}

// copy constructor
// texture is copied into OUR member first, then sprite is rebuilt pointing at OUR texture
// if we just copy sprite directly it keeps pointing at the other object's texture which
// gets destroyed when the temporary dies -> dangling pointer -> assertion crash
platform::platform(const platform& other) : texture(other.texture), sprite(texture)
{
    body = other.body;
    frameRect = other.frameRect;
    posX = other.posX;
    posY = other.posY;
    width = other.width;
    height = other.height;

    // rebuild sprite so it points at THIS object's texture, not other's
    sprite = sf::Sprite(texture, frameRect);
    sprite.setScale(other.sprite.getScale());
    sprite.setPosition(other.sprite.getPosition());
}

platform& platform::operator=(const platform& other)
{
    if (this == &other)
    {
        return *this;
    }

    texture = other.texture;
    body = other.body;
    frameRect = other.frameRect;
    posX = other.posX;
    posY = other.posY;
    width = other.width;
    height = other.height;

    // rebuild sprite pointing at THIS object's texture
    sprite = sf::Sprite(texture, frameRect);
    sprite.setScale(other.sprite.getScale());
    sprite.setPosition(other.sprite.getPosition());

    return *this;
}

sf::RectangleShape& platform::getBody()
{
    return body;
}

void platform::draw(sf::RenderWindow& window)
{
    window.draw(sprite);
}

float platform::getX()
{
    return posX;
}

float platform::getY()
{
    return posY;
}

float platform::getWidth()
{
    return width;
}

float platform::getHeight()
{
    return height;
}
