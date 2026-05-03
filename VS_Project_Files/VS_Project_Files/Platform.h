#pragma once
#include<SFML/Graphics.hpp>

class platform {
private:
	sf::RectangleShape body;

	float posX;
	float posY;
	float width;
	float height;

	sf::Texture texture;
	sf::Sprite sprite;
	sf::IntRect frameRect;
public:
	platform();
	platform(const platform& other);
	platform(float x, float y, float width, float height);
	platform& operator=(const platform& other);

	sf::RectangleShape& getBody();
	void draw(sf::RenderWindow& window);

	float getX();
	float getY();
	float getWidth();
	float getHeight();

	
};