#include "GameObjects.h"


GameObject::GameObject(float x, float y, bool active, float w, float h)
{
    posX = x;
    posY = y;
    isActive = active;
    width = w;
    height = h;
}


GameObject::~GameObject()
{
}

float GameObject::getX() 
{ 
    return posX; 
}
float GameObject::getY() 
{ 
    return posY; 
}
float GameObject::getWidth() 
{ 
    return width; 
}
float GameObject::getHeight()
 {
    return height; 
}
bool GameObject::getActive() 
{ 
    return isActive;
}

void GameObject::setPosition(float x, float y) 
{
    posX = x;
    posY = y;
}

void GameObject::setColliders(float x, float y) 
{
    width = x;
    height = y;
}

void GameObject::setActive(bool active)
{
    isActive = active;
}