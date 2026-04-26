#pragma once
#include <SFML/Graphics.hpp>
using namespace std;

class GameObject
{
	float posX;
	float posY;
	bool isActive; // is it in the game
	float width;	// set width and height of collision of gameobject
	float height;

public:
	GameObject(float x, float y, bool active, float w, float h);
	virtual ~GameObject();

	float getX();
	float getY();
	float getWidth();
	float getHeight();
	bool getActive();

	void setPosition(float x, float y);
	void setColliders(float x, float y);
	void setActive(bool active);

	virtual void draw(sf::RenderWindow& window) = 0;// draws the object on the screen. it is differnt for each object
	// therefore is abstract

};
