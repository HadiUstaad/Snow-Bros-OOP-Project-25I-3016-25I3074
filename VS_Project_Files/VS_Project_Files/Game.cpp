#pragma once
#include"Game.h"
#include<SFML/Graphics.hpp>
#include "MenuDisplay.h"



game::game()
    : window(sf::VideoMode({ 800, 600 }), "Snow Bros") , ground(0,550, 800, 50)
{
    currentState = MENU;
}


void game::Run() {

    sf::CircleShape shape(50.f);
    shape.setFillColor(sf::Color::Green);
    shape.setPosition({ 375.f, 275.f });

    Menu mainMenu(window);

    while (window.isOpen()) {

        while (const std::optional event = window.pollEvent()) {

            if (event->is<sf::Event::Closed>())
                window.close();

            if (currentState == MENU && event->is<sf::Event::KeyPressed>()) {

                auto key = event->getIf<sf::Event::KeyPressed>();

                if (key && key->code == sf::Keyboard::Key::Enter) {

                    int selected = mainMenu.getSelectedIndex();

                    if (selected == 0)
                        currentState = PLAYING;

                    else if (selected == 3)
                        window.close();
                }
            }
        }

        input.update();

        if (currentState == MENU)
            mainMenu.handleInput();

        update();   // ONLY call here

        window.clear();

        if (currentState == MENU) {
            mainMenu.draw();
        }
        else if (currentState == PLAYING) {
            ground.draw(window);
            player.draw(window);
        }

        window.display();
    }
}

void game::update() {
    if (currentState == PLAYING) {
        player.update(input,ground);
    }
}

