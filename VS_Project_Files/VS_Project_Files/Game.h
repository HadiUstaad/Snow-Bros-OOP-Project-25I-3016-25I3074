#pragma once
#include"Player.h"
#include"Input.h"
#include"Platform.h"
#include "Botom.h"
#include "Ball.h"
#include "Fooga.h"
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
    Player player1;
    Player player2;
    Input input1;
    Input input2;

    //Enemy
    Boton boton;
    Fooga fooga;

    //Ball
    Ball B1;//player 1 ball
    Ball B2;//player 2 ball

    //multiple platforms a
    static const int MAX_PLATFORMS = 5;
    platform platforms[MAX_PLATFORMS];

    sf::Clock clock;

    //Hit box
    bool Hitbox;
    bool EnemyHitbox;

public:
    game();
    void Run();
    void update();
};


