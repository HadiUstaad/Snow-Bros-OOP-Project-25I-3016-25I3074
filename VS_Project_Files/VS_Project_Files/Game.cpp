#pragma once
#include"Game.h"
#include<SFML/Graphics.hpp>
#include "MenuDisplay.h"



game::game()
    : window(sf::VideoMode({ 800, 600 }), "Snow Bros")   
{
    currentState = MENU;
}

void game::Run() {

    sf::CircleShape shape(50.f);
    shape.setFillColor(sf::Color::Green);
    shape.setPosition({ 375.f, 275.f });

    Menu mainMenu(window);

    while (window.isOpen()) {

        // Handle events
        while (const std::optional event = window.pollEvent()) {

            if (event->is<sf::Event::Closed>())
                window.close();

            if (currentState == MENU) {
                if (event->is<sf::Event::KeyPressed>()) {

                    auto key = event->getIf<sf::Event::KeyPressed>();
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter))
                    {

                        int selected = mainMenu.getSelectedIndex();

                        if (selected == 0) {         // 0 = "New Game"
                            currentState = PLAYING;
                        }
                        else if (selected == 4) {    // 4 = "Exit"
                            window.close();
                        }
                    }
                }
            }
        }

        //  ALWAYS RUN EVERY FRAME
        input.update();   // moved outside
        update();         // moved outside

        // handling input is also updating it
        if (currentState == MENU) 
        {
            mainMenu.handleInput();
        }

        window.clear();

        if (currentState == MENU) 
        {
            mainMenu.draw();
        }
        else if (currentState == PLAYING) {
            window.draw(shape);
            player.draw(window); // (when added)
        }

        window.display();
    }
}

void game::update() {
    if (currentState == PLAYING) {
        player.update(input);
    }
}

