#pragma once
#include"Player.h"
#include"Input.h"
#include"Platform.h"
#include "Botom.h"
#include "Ball.h"
#include<iostream>
using namespace std;


//enum variables
enum GameState {
    MENU,
    PLAYING
};


class game {
private:
    sf::RenderWindow window;
    GameState currentState;

    //objects of player and input manager
    Player player;
    Input input;

    //Enemy
    Boton boton;

    //Ball
    Ball B;

    //multiple platforms a
    static const int MAX_PLATFORMS = 5;
    platform platforms[MAX_PLATFORMS];

    sf::Clock clock;

    //Hit box
    bool Hitbox;

public:
    game();
    void Run();
    void update();
};


