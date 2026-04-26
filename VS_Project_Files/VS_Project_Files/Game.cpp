//#pragma once
//#include"Game.h"
//#include<SFML/Graphics.hpp>
//#include "MenuDisplay.h"
//#include"Ball.h"
//
//
//
//
//game::game()
//    : window(sf::VideoMode({ 800, 600 }), "Snow Bros") , boton(520,100) 
//{
//    currentState = MENU;
//platforms[0] = platform(0, 550, 800, 50);   // ground
//platforms[1] = platform(0, 425, 400, 20);
//platforms[2] = platform(400, 320, 400, 20);
//platforms[3] = platform(0, 220, 350, 20);
//platforms[4] = platform(400, 120, 400, 20);
//
//Hitbox = false;
//
//}
//
//
//void game::Run() {
//
//    sf::CircleShape shape(50.f);
//    shape.setFillColor(sf::Color::Green);
//    shape.setPosition({ 375.f, 275.f });
//
//    Menu mainMenu(window);
//
//    while (window.isOpen()) {
//
//        while (const std::optional event = window.pollEvent()) {
//
//            if (event->is<sf::Event::Closed>())
//                window.close();
//
//            if (event->is<sf::Event::KeyPressed>()) {
//
//                auto key = event->getIf<sf::Event::KeyPressed>();
//
//                if (event->is<sf::Event::KeyPressed>()) {
//                    auto key = event->getIf<sf::Event::KeyPressed>();
//
//                    if (key && key->code == sf::Keyboard::Key::F) {
//
//                        int direction = 1; // later we use player direction
//
//                        B.shoot(
//                            player.getBounds().position.x,
//                            player.getBounds().position.y,
//                            direction
//                        );
//                    }
//                }
//
//                if (key && key->code == sf::Keyboard::Key::H) {
//                    Hitbox = !Hitbox;
//                }
//
//                if (key && key->code == sf::Keyboard::Key::Enter) {
//
//                    int selected = mainMenu.getSelectedIndex();
//
//                    if (selected == 0)
//                        currentState = PLAYING;
//
//                    else if (selected == 3)
//                        window.close();
//                }
//            }
//        }
//
//        input.update();
//
//        if (currentState == MENU)
//            mainMenu.handleInput();
//
//        update();   // ONLY call here
//
//        window.clear();
//
//        if (currentState == MENU) {
//            mainMenu.draw();
//        }
//        else if (currentState == PLAYING) {
//            for (int i = 0; i < MAX_PLATFORMS; i++) {
//                platforms[i].draw(window);
//
//                if (Hitbox) {
//                    sf::RectangleShape box;
//                    box.setSize(platforms[i].getBody().getSize());
//                    box.setPosition(platforms[i].getBody().getPosition());
//                    box.setFillColor(sf::Color::Transparent);
//                    box.setOutlineColor(sf::Color::Yellow);
//                    box.setOutlineThickness(1);
//
//                    window.draw(box);
//                }
//            }
//            player.draw(window);
//            boton.draw(window);
//
//            player.draw(window);
//
//            B.draw(window);//Ball
//
//            //player hitbox 
//            if (Hitbox) {
//                player.drawHitbox(window);
//            }
//        }
//        B.update(); //Ball
//        window.display();
//    }
//}
//
//void game::update() {
//    if (currentState == PLAYING) {
//        float deltaTime = clock.restart().asSeconds(); // resets clock every frame so that movement is same in all FPS
//        player.update(input, platforms, MAX_PLATFORMS);
//        boton.updateMovement(0.003f,platforms,MAX_PLATFORMS);
//
//
//        if (player.getBounds().findIntersection(boton.getBounds())) {
//            player.Reset();   // simple response
//        }
//    }
//
//    if (B.checkactive() && B.getbounds().findIntersection(boton.getBounds())) {
//        // simple response
//        B = Ball();   // reset
//    }
//}
//


#include "Game.h"
#include <SFML/Graphics.hpp>
#include "MenuDisplay.h"
#include "Ball.h"

game::game()
    : window(sf::VideoMode({ 800, 600 }), "Snow Bros") , boton(520,100) ,fooga(20,180)
{
    currentState = MENU;

    platforms[0] = platform(0, 550, 800, 50);
    platforms[1] = platform(0, 425, 400, 20);
    platforms[2] = platform(400, 320, 400, 20);
    platforms[3] = platform(0, 220, 350, 20);
    platforms[4] = platform(400, 120, 400, 20);

    Hitbox = false;
}

void game::Run()
{
    Menu mainMenu(window);

    while (window.isOpen())
    {
        // 🔥 EVENT LOOP (SFML 3)
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();

            if (event->is<sf::Event::KeyPressed>())
            {
                auto key = event->getIf<sf::Event::KeyPressed>();

                // 🔥 SHOOT
                if (key && key->code == sf::Keyboard::Key::F)
                {
                    int direction = 1;

                    B.shoot(
                        player.getBounds().position.x,
                        player.getBounds().position.y,
                        direction
                    );
                }

                // 🔥 HITBOX TOGGLE
                if (key && key->code == sf::Keyboard::Key::H)
                {
                    Hitbox = !Hitbox;
                }

                    else if (selected == 4)
                        window.close();
                }
            }
        }

        // 🔥 INPUT UPDATE
        input.update();

        if (currentState == MENU)
            mainMenu.handleInput();

        // 🔥 GAME UPDATE
        update();
        B.update();   // Snowball update MUST be before rendering

        // 🔥 RENDER
        window.clear();

        if (currentState == MENU)
        {
            mainMenu.draw();
        }
        else if (currentState == PLAYING)
        {
            // platforms
            for (int i = 0; i < MAX_PLATFORMS; i++)
            {
                platforms[i].draw(window);

                if (Hitbox)
                {
                    sf::RectangleShape box;
                    box.setSize(platforms[i].getBody().getSize());
                    box.setPosition(platforms[i].getBody().getPosition());
                    box.setFillColor(sf::Color::Transparent);
                    box.setOutlineColor(sf::Color::Yellow);
                    box.setOutlineThickness(1);

                    window.draw(box);
                }
            }
            
            

            // objects
            player.draw(window);
            boton.draw(window);
            fooga.draw(window);
            B.draw(window);

            // player hitbox
            if (Hitbox)
                player.drawHitbox(window);
        }

        window.display();
    }
}

void game::update()
{
    if (currentState == PLAYING)
    {
        float deltaTime = clock.restart().asSeconds();

        player.update(input, platforms, MAX_PLATFORMS);
        boton.updateMovement(0.003f, platforms, MAX_PLATFORMS);

        // 🔥 PLAYER vs ENEMY
        if (player.getBounds().findIntersection(boton.getBounds()))
        {
            player.Reset();
        }
        
        fooga.updateMovement(0.002f,platforms,MAX_PLATFORMS);
    }
}

        // 🔥 SNOWBALL vs ENEMY
        if (B.checkactive() && B.getbounds().findIntersection(boton.getBounds()))
        {
            if (B.checkactive() && B.getbounds().findIntersection(boton.getBounds())) {

                boton.freeze();   // ❄️ freeze enemy
                B = Ball();       // remove snowball
            }  // reset snowball
        }
    }
}