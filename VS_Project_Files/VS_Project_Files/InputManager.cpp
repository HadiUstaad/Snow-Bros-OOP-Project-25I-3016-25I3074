#include"Input.h"
#include<SFML/Graphics.hpp>

void Input::update() {

    left = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A);
    right = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D);

    static bool prevJump = false;

    bool currentJump = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W);

    if (currentJump && !prevJump) {
        jumppressed = true;
    }
    else {
        jumppressed = false;
    }

    prevJump = currentJump;
}