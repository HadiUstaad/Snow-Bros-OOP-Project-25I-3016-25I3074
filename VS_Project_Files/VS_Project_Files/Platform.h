#pragma once
#include<SFML/Graphics.hpp>

class platform {
private:
	sf::RectangleShape body;

public:

	platform(float x, float y, float width, float height);

	sf::RectangleShape& getbody();
	void draw(sf::RenderWindow& window);
};