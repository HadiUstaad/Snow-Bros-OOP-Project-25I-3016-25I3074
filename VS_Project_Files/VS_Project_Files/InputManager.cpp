#include"Input.h"
#include<SFML/Graphics.hpp>

void Input::update() {
	left = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A);
	right = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D);
	jump = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W);

}