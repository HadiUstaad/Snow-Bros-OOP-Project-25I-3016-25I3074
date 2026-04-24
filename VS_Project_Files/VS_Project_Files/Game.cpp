#pragma once
#include"Game.h"
#include<SFML/Graphics.hpp>
#include "MenuDisplay.h"





game::game()
    : window(sf::VideoMode({ 800, 600 }), "Snow Bros") , boton(520,100)
{
    currentState = MENU;
platforms[0] = platform(0, 550, 800, 50);   // ground
platforms[1] = platform(100, 450, 200, 20);
platforms[2] = platform(400, 350, 200, 20);
platforms[3] = platform(150, 250, 150, 20);
platforms[4] = platform(500, 150, 150, 20);

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
            for (int i = 0; i < MAX_PLATFORMS; i++) {
                platforms[i].draw(window);
            }
            player.draw(window);
            boton.draw(window);
        }

        window.display();
    }
}

void game::update() {
    if (currentState == PLAYING) {
        float deltaTime = clock.restart().asSeconds(); // resets clock every frame so that movement is same in all FPS
        player.update(input, platforms, MAX_PLATFORMS);
        boton.updateMovement(0.0005f,platforms,MAX_PLATFORMS);
    }
}

