#pragma once
#include"Player.h"
#include"Input.h"
#include"Platform.h"
#include "Botom.h"
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

    //multiple platforms a
    static const int MAX_PLATFORMS = 5;
    platform platforms[MAX_PLATFORMS];

    sf::Clock clock;

public:
    game();
    void Run();
    void update();
};


