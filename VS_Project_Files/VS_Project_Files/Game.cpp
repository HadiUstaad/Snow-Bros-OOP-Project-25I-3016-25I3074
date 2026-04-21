#pragma once
#include"Game.h"
#include<SFML/Graphics.hpp>



game::game()
    : window(sf::VideoMode({ 800, 600 }), "Snow Bros")   
{
    currentState = MENU;
}

void game::Run() {

    sf::CircleShape shape(50.f);
    shape.setFillColor(sf::Color::Green);
    shape.setPosition({ 375.f, 275.f });

    while (window.isOpen()) {

        // 🔹 Handle events
        while (const std::optional event = window.pollEvent()) {

            if (event->is<sf::Event::Closed>())
                window.close();

            if (currentState == MENU) {
                if (event->is<sf::Event::KeyPressed>()) {

                    auto key = event->getIf<sf::Event::KeyPressed>();

                    if (key->code == sf::Keyboard::Key::Enter) {
                        currentState = PLAYING;
                    }
                }
            }
        }

        // RUN EVERY FRAME
        input.update();   
        update();         

        window.clear();

        if (currentState == MENU) {
            // menu later
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

