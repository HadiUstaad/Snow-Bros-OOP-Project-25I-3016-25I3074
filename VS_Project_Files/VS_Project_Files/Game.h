#pragma once
#include"Player.h"
#include"Input.h"
#include"Platform.h"
#include "Botom.h"
#include "Ball.h"
#include "Fooga.h"
#include<iostream>
#include<string>
#include"LeaderBoard.h"
#include "DatabaseManagement.h"
#include<SFML/Graphics.hpp>
using namespace std;


//enum variables
enum GameState {
    MENU,
    PLAYING,
    LEADER_BOARD,
    GAME_OVER

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


    int score1;
    int score2;

    sf::Font font;
    sf::Text scoreText1;
    sf::Text scoreText2;

    int currentLevel;
    Enemies* enemies[15];   // max enemies per level
    int enemyCount;
    bool AllDead();
    //sf::Text wintext;

    sf::Text levelText;
    float levelDisplayTimer;
    bool showLevelText;

    //lives system
    int lives1;
    int lives2;

    sf::Text livesText1;
    sf::Text livesText2;

    //Game over
    bool gameOverPrinted;
    bool winPrinted;
    sf::Text gameOverText;
    //sf::Texture heartTexture;
    //sf::Sprite heartSprite1[3]; // player 1
    //sf::Sprite heartSprite2[3]; // player 2

    // Database and Leaderboard system
    FileManage* fileManager;           
    LeaderboardScreen* leaderboard;    
    string playerName1;              
    string playerName2;

public:
    game();
    void Run();
    void update();
    void UpdatescoreUI();
    void loadLevel(int level);

    ~game();                  
    void submitScores();      
    void showLeaderboard();    
    void hideLeaderboard(); 
};


