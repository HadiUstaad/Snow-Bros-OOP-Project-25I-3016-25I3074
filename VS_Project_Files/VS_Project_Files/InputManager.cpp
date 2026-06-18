#include"Input.h"
#include<SFML/Graphics.hpp>


//Player 1
void Input::updatePlayer1() {

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

//Player2
void Input::updatePlayer2() {

    static bool prevJump = false;
    left = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left);
    right = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right);
    jump = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up);

    bool currentJump = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up);

    if (currentJump && !prevJump) {
        jumppressed = true;
    }
    else {
        jumppressed = false;
    }

    prevJump = currentJump;
}