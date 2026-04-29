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
#include"FlyingEnemy.h"
#include"Fooga.h"

game::game()
    : window(sf::VideoMode({ 800, 600 }), "Snow Bros") , boton(520,100) ,fooga(20,180) 
{
    currentState = MENU;

    

    platforms[0] = platform(0, 550, 800, 50);
    platforms[1] = platform(0, 425, 400, 20);
    platforms[2] = platform(400, 320, 400, 20);
    platforms[3] = platform(0, 220, 350, 20);
    platforms[4] = platform(400, 120, 400, 20);


    player1.setPosition(100,300);
    player2.setPosition(300,100);

    Hitbox = false;
    EnemyHitbox = false;
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
                    //int direction = 1;

                    B1.shoot(
                        player1.getBounds().position.x,
                        player1.getBounds().position.y,
                        player1.getDirection()
                    );
                }
                if (key && key->code == sf::Keyboard::Key::RShift)
                {
                    //int direction = 1;

                    B2.shoot(
                        player2.getBounds().position.x,
                        player2.getBounds().position.y,
                        player2.getDirection()
                    );
                }

                // 🔥 HITBOX TOGGLE
                if (key && key->code == sf::Keyboard::Key::H)
                {
                    Hitbox = !Hitbox;
                }

                if (key && key->code == sf::Keyboard::Key::J)
                {
                    EnemyHitbox = !EnemyHitbox;
                }

                if (key && key->code == sf::Keyboard::Key::Enter) {
                    
                    int selected = mainMenu.getSelectedIndex();
                    
                    if (selected == 0)
                        currentState = PLAYING;
                    
                    else if (selected == 4)
                        window.close();
                }
                
            }
        }

        // 🔥 INPUT UPDATE
        input1.updatePlayer1();
        input2.updatePlayer2();
        if (currentState == MENU)
            mainMenu.handleInput();

        // 🔥 GAME UPDATE
        update();
        B1.update();
        B2.update();// Snowball update MUST be before rendering

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
            player1.draw(window);
            player2.draw(window);
            boton.draw(window);
            fooga.draw(window);
            B1.draw(window);
            B2.draw(window);
            // player hitbox
            if (Hitbox)
                player1.drawHitbox(window);
            player2.drawHitbox(window);
            if (EnemyHitbox)
            {
                boton.drawHitbox(window);
                fooga.drawHitbox(window);
            }
        }

        window.display();
    }
}

void game::update()
{
    if (currentState == PLAYING)
    {
        float deltaTime = clock.restart().asSeconds();

        player1.update(input1, platforms, MAX_PLATFORMS);
        player2.update(input2, platforms, MAX_PLATFORMS);
        boton.updateMovement(0.002f, platforms, MAX_PLATFORMS);
        fooga.updateMovement(0.002f,platforms,MAX_PLATFORMS);

        // 🔥 PLAYER vs ENEMY
        if (boton.isAlive() && player1.getBounds().findIntersection(boton.getBounds()))
        {
            player1.Reset();
        }
        if (boton.isAlive() && player2.getBounds().findIntersection(boton.getBounds()))
        {
            player2.Reset();
        }
        // player vs fooga
        if (fooga.isAlive() && player1.getBounds().findIntersection(fooga.getBounds()))
        {
            player1.Reset();   // Kill player
        }
        if (fooga.isAlive() && player2.getBounds().findIntersection(fooga.getBounds()))
        {
            player2.Reset();   // Kill player
        }


        // 🔥 SNOWBALL vs ENEMY
        if (boton.isAlive() && B1.checkactive() && B1.getbounds().findIntersection(boton.getBounds()))
        {
            
            if (B1.checkactive() && B1.getbounds().findIntersection(boton.getBounds())) {

                boton.onHit();  // ❄️ freeze enemy
                B1 = Ball();       // remove snowball
            }  // reset snowball
        }

        if (B1.checkactive() && fooga.isAlive() && B1.getbounds().findIntersection(fooga.getBounds()))
        {
            fooga.onHit();     // Hit Fooga with snowball
            B1 = Ball();        // Reset snowball
        }

        if (boton.isAlive() && B2.checkactive() && B2.getbounds().findIntersection(boton.getBounds()))
        {

            if (B2.checkactive() && B2.getbounds().findIntersection(boton.getBounds())) {

                boton.onHit();  // ❄️ freeze enemy
                B2 = Ball();       // remove snowball
            }  // reset snowball
        }

        if (B2.checkactive() && fooga.isAlive() && B2.getbounds().findIntersection(fooga.getBounds()))
        {
            fooga.onHit();     // Hit Fooga with snowball
            B2 = Ball();        // Reset snowball
        }

        //if (boton.isAlive() &&
        //    player.getBounds().findIntersection(boton.getBounds()))
        //{
        //    player.Reset();
        //}
    }
}