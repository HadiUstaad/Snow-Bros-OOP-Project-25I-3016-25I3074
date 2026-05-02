#pragma once
#include "Game.h"
#include <SFML/Graphics.hpp>
#include "MenuDisplay.h"
#include "Ball.h"
#include"FlyingEnemy.h"
#include"Fooga.h"
#include <cstdlib>
#include <ctime>


game::game()
    : window(sf::VideoMode({ 800, 600 }), "Snow Bros") , boton(520,100) ,fooga(20,180) ,scoreText1(font, "P1: 0", 20),
    scoreText2(font, "P2: 0", 20) , levelText(font, "Level 1", 40) , livesText1(font, "Lives: 3", 20), livesText2(font, "Lives: 3", 20)
    , gameOverText(font, "GAME OVER", 50) , 
    levelCompleteText(font, "LEVEL COMPLETE", 50) , levelCompleteText2(font,"Press Enter to continue",20),bgTexture(),
    bgSprite(bgTexture)
{

    srand(time(0));// for random generation

    currentState = MENU;

    font.openFromFile("RussoOne-Regular.ttf");
    //heartTexture.loadFromFile("Heart.png");


    //Heart
    // Player 1 hearts (top-left)
    //for (int i = 0; i < 3; i++)
    //{
    //    heartSprite1[i].setTexture(heartTexture);
    //    heartSprite1[i].setScale({ 0.05f, 0.05f }); // adjust size
    //    heartSprite1[i].setPosition({ 10.f + i * 30.f, 40.f });
    //}

    //// Player 2 hearts (top-right)
    //for (int i = 0; i < 3; i++)
    //{
    //    heartSprite2[i].setTexture(heartTexture);
    //    heartSprite2[i].setScale({ 0.05f, 0.05f });
    //    heartSprite2[i].setPosition({ 650.f + i * 30.f, 40.f });
    //}

    // 🔥 NOW initialize text properly

    scoreText1.setCharacterSize(20);
    scoreText1.setFillColor(sf::Color::White);
    scoreText1.setPosition({ 10, 10 });

    scoreText2.setCharacterSize(20);
    scoreText2.setFillColor(sf::Color::White);
    scoreText2.setPosition({ 650, 10 });

    

    platforms[0] = platform(0, 550, 800, 50);
    platforms[1] = platform(0, 425, 400, 20);
    platforms[2] = platform(400, 320, 400, 20);
    platforms[3] = platform(0, 220, 350, 20);
    platforms[4] = platform(400, 120, 400, 20);


    player1.setPosition(100,300);
    player2.setPosition(300,100);

    Hitbox = false;
    EnemyHitbox = false;

    score1 = 0;
    score2 = 0;

    //level system
    currentLevel = 1;
    loadLevel(currentLevel);


    levelText.setFillColor(sf::Color::Yellow);
    levelText.setPosition({ 320, 50 });

    levelDisplayTimer = 2.0f;   // show for 2 seconds
    showLevelText = true;

    levelCompleteText.setFillColor(sf::Color::Green);
    levelCompleteText.setPosition({ 190, 250 });
    levelCompleteText2.setFillColor(sf::Color::Green);
    levelCompleteText2.setPosition({ 280,330});

    invincibleTimer1 = 0;
    invincibleTimer2 = 0;


    //lives
    lives1 = 3;
    lives2 = 3;

    livesText1.setPosition({ 10, 40 });
    livesText2.setPosition({ 650, 40 });

    //Gameover
    winPrinted = false;
    gameOverPrinted = false;
    gameOverText.setFillColor(sf::Color::Red);
    gameOverText.setPosition({ 200, 250 });

    //LeaderBoard
   
    fileManager = new FileManage("snowbros_Hazai.db");   // db is extension of data base files.
    leaderboard = new LeaderboardScreen(window, fileManager);
    playerName1 = "P3";         // Modify these later when taken from login.
    playerName2 = "P1";
    fileManager->addUser(playerName1, "000000000");
    fileManager->addUser(playerName2, "000000000");

}

game::~game()
{
    // check to see ke leaderboard exist karta bhi hai ya nhi. 
    // if not exist avoid error by deleting
    if (leaderboard != 0)   
    {
        delete leaderboard;
    }

    if (fileManager != 0)
    {
        delete fileManager;
    }
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

                if (key && key->code == sf::Keyboard::Key::Escape)
                {
                    if (currentState == GAME_OVER)
                    {
                        // Reset game variables so for next play
                        lives1 = 3;
                        lives2 = 3;
                        score1 = 0;
                        score2 = 0;
                        currentLevel = 1;
                        gameOverPrinted = false;
                        loadLevel(1);

                        currentState = MENU; 
                    }
                   
                }

                if (key && key->code == sf::Keyboard::Key::Enter) {
                    
                    int selected = mainMenu.getSelectedIndex();
                    
                    if (selected == 0)
                        currentState = PLAYING;

                    else if (selected == 2)
                    {
                        currentState = LEADER_BOARD;
                        showLeaderboard();
                    }
                    
                    else if (selected == 4)
                        window.close();
                }
                if (currentState == LEVEL_COMPLETE && key && key->code == sf::Keyboard::Key::Enter)
                {
                    currentLevel++;

                    if (currentLevel <= 10)
                    {
                        loadLevel(currentLevel);
                        currentState = PLAYING;
                    }
                }
                
            }

        }

        // 🔥 INPUT UPDATE
        input1.updatePlayer1();
        input2.updatePlayer2();
        if (currentState == MENU)
            mainMenu.handleInput();
        else if (currentState == LEADER_BOARD)
        {
            leaderboard->handleInput();
        }

       
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

            float deltaTime = clock.restart().asSeconds();

      
            if (showLevelText)
            {
                levelDisplayTimer -= deltaTime;

                if (levelDisplayTimer <= 0)
                {
                    showLevelText = false;
                }
            }
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

            //coins spawn
            for (int i = 0; i < coinCount; i++)
            {
                if (coinActive[i])
                    window.draw(coins[i]);
            }
            
            //levels
            window.draw(bgSprite);
            // objects
            player1.draw(window);
            player2.draw(window);
            

            for (int i = 0; i < enemyCount; i++)
            {
                enemies[i]->draw(window);//for multiple enemies
            }
            B1.draw(window);
            B2.draw(window);
            window.draw(scoreText1);
            window.draw(scoreText2);
            // player hitbox
            if (Hitbox)
            player1.drawHitbox(window);
            player2.drawHitbox(window);
            player2.drawHitbox(window);
            if (EnemyHitbox)
            {
                boton.drawHitbox(window);
                fooga.drawHitbox(window);
            }

            if (showLevelText)
            {
                window.draw(levelText);
            }
            window.draw(livesText1);
            window.draw(livesText2);

          
        }
        else if (currentState == LEADER_BOARD)
        {
            leaderboard->draw();  

            // Check if user pressed ESC
            if (leaderboard->getIsVisible() == false)
            {
                currentState = MENU;  // Return to menu
                leaderboard->show();  // Reset visibility of menu
            }
        }
        else if (currentState == LEVEL_COMPLETE)
        {
            window.draw(levelCompleteText);
            window.draw(levelCompleteText2);
        }
        else if (currentState == GAME_OVER)
        {
            if (!gameOverPrinted)
            {
                cout << "GAME OVER" << endl;
                gameOverPrinted = true;
            }

            window.draw(gameOverText);
        }
       

        window.display();
    }
}

void game::update()
{
    if (currentState == PLAYING)
    {
        float deltaTime = clock.restart().asSeconds();

        if (invincibleTimer1 > 0)
            invincibleTimer1 -= deltaTime;
    
        if (invincibleTimer2 > 0) 
            invincibleTimer2 -= deltaTime;
        

        player1.update(input1, platforms, MAX_PLATFORMS);
        player2.update(input2, platforms, MAX_PLATFORMS);
        //boton.updateMovement(0.002f, platforms, MAX_PLATFORMS);
        //fooga.updateMovement(0.002f,platforms,MAX_PLATFORMS);

        for (int i = 0; i < enemyCount; i++)
        {
            enemies[i]->updateMovement(0.002f, platforms, MAX_PLATFORMS);
        }

       
        for (int i = 0; i < enemyCount; i++)
        {
            // modify add clock for collision spaces 
            if (enemies[i]->isAlive() && lives1 > 0 &&
                player1.getBounds().findIntersection(enemies[i]->getBounds()) && invincibleTimer1 <= 0)
            {
                lives1--;
                invincibleTimer1 = 1.0f;

                if (lives1 > 0)
                {
                    player1.Reset();
                }
            }

            if (enemies[i]->isAlive() && lives2 > 0 &&
                player2.getBounds().findIntersection(enemies[i]->getBounds()) && invincibleTimer2 <= 0)
            {
                lives2--;
                invincibleTimer2 = 1.0f;

                if (lives2 > 0)
                {
                    player2.Reset();
                }
            }
        }


        

        for (int i = 0; i < enemyCount; i++)
        {
            if (enemies[i]->isAlive() &&
                B1.checkactive() &&
                B1.getbounds().findIntersection(enemies[i]->getBounds()))
            {
                enemies[i]->onHit();

                if (!enemies[i]->isAlive())
                    score1 += 100;

                B1 = Ball();
            }
        }

        

        for (int i = 0; i < enemyCount; i++)
        {
            if (enemies[i]->isAlive() &&
                B2.checkactive() &&
                B2.getbounds().findIntersection(enemies[i]->getBounds()))
            {
                enemies[i]->onHit();

                if (!enemies[i]->isAlive())
                    score2 += 100;

                B2 = Ball();
            }
        }
       

        scoreText1.setString("P1: " + to_string(score1));
        scoreText2.setString("P2: " + to_string(score2));
        livesText1.setString("P1 Lives: " + std::to_string(lives1));
        livesText2.setString("P2 Lives: " + std::to_string(lives2));
    }

    if (AllDead() && !winPrinted)
    {
        currentLevel++;
        if (AllDead())
        {
            currentState = LEVEL_COMPLETE;   // pause game
        }

        if (currentLevel <= 10)
        {
            loadLevel(currentLevel);
        }
        else
        {
            cout << "YOU WIN!" << endl;
            winPrinted = 1;
        }
    }

    //game over condition
    if (lives1 <= 0 && lives2 <= 0)
    {
        // this submits scores before showing game over screen
        if (gameOverPrinted == false)
        {
            submitScores();
        }
        currentState = GAME_OVER;
        return;
    }

    //coins
    for (int i = 0; i < coinCount; i++)
    {
        if (coinActive[i] &&
            player1.getBounds().findIntersection(coins[i].getGlobalBounds()))
        {
            coinActive[i] = false;
            score1 += 50;
        }

        if (coinActive[i] &&
            player2.getBounds().findIntersection(coins[i].getGlobalBounds()))
        {
            coinActive[i] = false;
            score2 += 50;
        }
    }

    UpdatescoreUI();
}

void game::UpdatescoreUI() {
    scoreText1.setString("P1: " + std::to_string(score1));
    scoreText2.setString("P2: " + std::to_string(score2));

}

//level functions

void game::loadLevel(int level)
{
  

    if (level == 1)
    {

        if (!bgTexture.loadFromFile("./level1.png.png"))
        {
            cout << "Background not loading\n";
        }
        else {
            cout << "Background loaded";
            bgSprite = sf::Sprite(bgTexture);
        }
        bgSprite.setTexture(bgTexture);
        bgSprite.setScale({800.0f / bgTexture.getSize().x,600.0f / bgTexture.getSize().y});
        enemyCount = 2;
        enemies[0] = new Boton(520, 100);
        enemies[1] = new Fooga(20, 180);

        platformCount = 3;

        platforms[0] = platform(0, 550, 800, 50);
        platforms[1] = platform(100, 400, 200, 20);
        platforms[2] = platform(400, 300, 200, 20);
    }
    else if (level == 2)
    {
        enemyCount = 3;
        enemies[0] = new Boton(100, 300);
        enemies[1] = new Boton(400, 200);
        enemies[2] = new Fooga(200, 100);

        platformCount = 4;

        platforms[0] = platform(0, 550, 800, 50);
        platforms[1] = platform(0, 450, 300, 20);
        platforms[2] = platform(500, 350, 300, 20);
        platforms[3] = platform(200, 250, 200, 20);
    }
    else if (level == 3)
    {
        enemyCount = 4;
        enemies[0] = new Boton(100, 300);
        enemies[1] = new Boton(300, 300);
        enemies[2] = new Fooga(200, 150);
        enemies[3] = new Fooga(500, 150);

        platformCount = 5;

        platforms[0] = platform(0, 550, 800, 50);
        platforms[1] = platform(100, 450, 200, 20);
        platforms[2] = platform(400, 450, 200, 20);
        platforms[3] = platform(250, 300, 200, 20);
        platforms[4] = platform(150, 150, 150, 20);
    }

    else
    {
        platformCount = 5;

        platforms[0] = platform(0, 550, 800, 50);
        platforms[1] = platform(50, 450, 200, 20);
        platforms[2] = platform(550, 400, 200, 20);
        platforms[3] = platform(250, 300, 300, 20);
        platforms[4] = platform(150, 180, 200, 20);
    }

    //// continue up to level 10

    //levelText.setString("Level " + std::to_string(level));
    //levelDisplayTimer = 2.0f;
    //showLevelText = true;

    coinCount = 0; // reset coins

    // BONUS LEVEL
    if (level == 4 || level == 9)
    {
        enemyCount = 0;

        coinCount = 5;

        for (int i = 0; i < coinCount; i++)
        {
            coins[i].setRadius(30);
            coins[i].setFillColor(sf::Color::Yellow);
            coins[i].setPosition({ float(100 + i * 120), 200 });
            coinActive[i] = true;
        }

        levelText.setString("BONUS LEVEL");
        levelDisplayTimer = 2.0f;
        showLevelText = true;

        return;
    }

    // NORMAL LEVELS
    enemyCount = level + 1;
    if (enemyCount > 10) enemyCount = 10;

    for (int i = 0; i < enemyCount; i++)
    {
        int pIndex = (platformCount > 1) ? (i % (platformCount - 1)) + 1 : 0;

        sf::Vector2f pPos = platforms[pIndex].getBody().getPosition();
        sf::Vector2f pSize = platforms[pIndex].getBody().getSize();

        float x = pPos.x + (i * 40) % int(pSize.x - 40);
        float y = pPos.y - 40;

        if (i % 2 == 0)
            enemies[i] = new Boton(x, y);
        else
            enemies[i] = new Fooga(x, y);

        float speedBoost = 0.001f * level;
        enemies[i]->setSpeed(enemies[i]->getSpeed() + speedBoost);
    }

    //for (int i = 0; i < enemyCount; i++)
    //{
    //    // pick a platform (skip ground → start from 1 if possible)
    //    int pIndex = (i % (platformCount - 1)) + 1;

    //    sf::Vector2f pPos = platforms[pIndex].getBody().getPosition();
    //    sf::Vector2f pSize = platforms[pIndex].getBody().getSize();

    //    float x = pPos.x + (rand() % int(pSize.x - 40)); // inside platform
    //    float y = pPos.y - 40; // on top of platform

    //    if (i % 2 == 0)
    //        enemies[i] = new Boton(x, y);
    //    else
    //        enemies[i] = new Fooga(x, y);

    //    // 🔥 difficulty scaling
    //    float speedBoost = 0.001f * level;
    //    enemies[i]->setSpeed(enemies[i]->getSpeed() + speedBoost);
    //}

    levelText.setString("Level " + std::to_string(level));
    levelDisplayTimer = 2.0f;
    showLevelText = true;
}


//Check whether all enemies are dead or not
bool game::AllDead()
{
   
    if (currentLevel == 4 || currentLevel == 9)
    {
        for (int i = 0; i < coinCount; i++)
        {
            if (coinActive[i])
                return false;
        }
        return true;
    }

    // normal enemy check
    for (int i = 0; i < enemyCount; i++)
    {
        if (enemies[i]->isAlive())
            return false;
    }

    return true;
}


// Submit both player scores to the database when both players die
void game::submitScores()
{
    
    if (playerName1.empty())  // only submit if name exists
    {
    }
    else
    {
        fileManager->addScore(playerName1, score1);
    }
 
    if (!playerName2.empty())  
    {
        fileManager->addScore(playerName2, score2);
    }

    // Update leaderboard display with new scores
    leaderboard->updateLeaderboard();
}

// change gamestae to leaderboard
void game::showLeaderboard()
{
    // refresh before showing
    leaderboard->updateLeaderboard();
    leaderboard->show();

    currentState = LEADER_BOARD;
}

// return to menu
void game::hideLeaderboard()
{
    leaderboard->hide();
    currentState = MENU;
}