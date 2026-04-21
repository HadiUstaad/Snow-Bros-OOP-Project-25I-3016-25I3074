#include"Platform.h"
#include<SFML/Graphics.hpp>

platform::platform(float x, float y, float width, float height) {
	body.setSize({ width,height });
	body.setPosition({ x,y });
	body.setFillColor(sf::Color::Red);
}


sf::RectangleShape& platform::getbody() {
	return body;
}


void platform::draw(sf::RenderWindow& window) {
	window.draw(body);
}
