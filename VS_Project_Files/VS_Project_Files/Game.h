#pragma once
#include"Player.h"
#include"Input.h"
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

public:
    game();
    void Run();
    void update();
};


