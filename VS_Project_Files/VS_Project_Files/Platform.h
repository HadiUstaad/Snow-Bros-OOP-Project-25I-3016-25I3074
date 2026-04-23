#pragma once
#include<SFML/Graphics.hpp>

class platform {
private:
	sf::RectangleShape body;

public:
	platform();

	platform(float x, float y, float width, float height);

	sf::RectangleShape& getBody();
	void draw(sf::RenderWindow& window);
};