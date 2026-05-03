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
#include "Pause.h"
#include "Currency.h"
#include "Mogera.h"
#include "Mogera_child.h"
#include "Gamakichi.h"
#include "Gamakichi_rocket.h"
#include<SFML/Graphics.hpp>
#include"Login.h"
#include "Knife.h"
#include "Tornado.h"
#include"Authenticate.h"
#include"Shop.h"
using namespace std;


//enum variables
enum GameState {
    LOGIN,
    MENU,
    PLAYING,
    PAUSED,
    SHOP,
    LEADER_BOARD,
    LEVEL_COMPLETE,
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
    Mogera* BossMogera = nullptr;

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

    //Level system
    sf::Text levelText;
    float levelDisplayTimer;
    bool showLevelText;
    sf::Text levelCompleteText;
    sf::Text levelCompleteText2;
    float invincibleTimer1;
    float invincibleTimer2;

    //lives system
    int lives1;
    int lives2;

    sf::Text livesText1;
    sf::Text livesText2;

    sf::Texture bgTexture;
    sf::Sprite bgSprite;

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


    //Bonuses 
    //coins
    sf::CircleShape coins[10];
    bool coinActive[10];
    int coinCount;
    int CointoGemValue;

    //PLatform
    int platformCount;

    //pause screen added
    PauseScreen* pauseScreen;


    // currency gems
    Currency gems1;
    Currency gems2;
    sf::Text gemText1;
    sf::Text gemText2;

   
    sf::RectangleShape bossHealthBarBg;
    sf::RectangleShape bossHealthBarFill;
    sf::Text bossHealthText;
    bool isBossLevel;       

    Gamakichi* BossGamakichi = nullptr;
    void spawnMogeraChildren();     
    void updateBossHealthBar();   

    //login system
    Authenticate* authManager;
    LoginScreen* loginScreen;


    //shop
    ShopScreen* shopScreen;
    PowerUpState powerUpState;
    int activePlayer;
    void spawnGamakichiChildren();
    void updateGamakichiBossHealthBar();

    // knife array. max 12 knives on screen. static variable so that it can be changed from one place in code but not inside code
    static const int MAX_KNIVES = 12;
    Knife* knives[MAX_KNIVES];
    int knifeCount;


public:
    game();
    void Run();
    void update(float deltatime);
    void UpdatescoreUI();
    void loadLevel(int level);

    ~game();                  
    void submitScores();      
    void showLeaderboard();    
    void hideLeaderboard(); 

    void updateKnives(float deltaTime);
    void checkKnifePlayerCollisions();
};


