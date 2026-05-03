#pragma once
#include "Game.h"
#include <SFML/Graphics.hpp>
#include "MenuDisplay.h"
#include "Ball.h"
#include"FlyingEnemy.h"
#include"Fooga.h"
#include"Login.h"
#include <cstdlib>
#include <ctime>


game::game()
    : window(sf::VideoMode({ 800, 600 }), "Snow Bros") , boton(520,100) ,fooga(20,180) ,scoreText1(font, "P1: 0", 20),
    scoreText2(font, "P2: 0", 20) , levelText(font, "Level 1", 40) , livesText1(font, "Lives: 3", 20), livesText2(font, "Lives: 3", 20)
    , gameOverText(font, "GAME OVER", 50) , 
    levelCompleteText(font, "LEVEL COMPLETE", 50) , levelCompleteText2(font,"Press Enter to continue",20),bgTexture(),
    bgSprite(bgTexture),
    gemText1(font, "P1 Gems: 0", 18),gemText2(font, "P2 Gems: 0", 18),
    bossHealthText(font, "BOSS HP", 14)
{

    srand(time(0));// for random generation

    currentState = MENU;

    font.openFromFile("RussoOne-Regular.ttf");
    

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

    CointoGemValue = 10;

    // null enemy pointer
    enemyCount = 0;
    for (int i = 0; i < 15; i++)
    {
        enemies[i] = nullptr;
    }
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

    livesText1.setPosition({ 10, 58 });
    livesText2.setPosition({ 620, 58 });

    //Gameover
    winPrinted = false;
    gameOverPrinted = false;
    gameOverText.setFillColor(sf::Color::Red);
    gameOverText.setPosition({ 200, 250 });

    //LeaderBoard
   
    fileManager = new FileManage("snowbros_Hazai.db");   // db is extension of data base files.
    leaderboard = new LeaderboardScreen(window, fileManager);
  
    playerName1 = "";
    playerName2 = "";

    authManager = new Authenticate(fileManager);
    loginScreen = new LoginScreen(window, authManager);

    currentState = LOGIN;

    // pause screen
    pauseScreen = new PauseScreen(window);

    //currency gem
    gemText1.setFillColor(sf::Color::Yellow);
    gemText1.setPosition({ 10, 35 });
    gemText2.setFillColor(sf::Color::Yellow);
    gemText2.setPosition({ 620, 35 });


    // Boss settings
    isBossLevel = false;

    bossHealthBarBg.setSize(sf::Vector2f(306, 24));
    bossHealthBarBg.setFillColor(sf::Color(80, 0, 0));
    bossHealthBarBg.setPosition({ 247, 11 });

    bossHealthBarFill.setSize(sf::Vector2f(300, 18));
    bossHealthBarFill.setFillColor(sf::Color::Red);
    bossHealthBarFill.setPosition({ 250, 8 });

    bossHealthText.setCharacterSize(13);
    bossHealthText.setFillColor(sf::Color::White);
    bossHealthText.setPosition({ 375, 10 });



    activePlayer = 0;
    shopScreen = new ShopScreen(window, &gems1, &gems2, &powerUpState);
    shopScreen->setActivePlayer(0);
    // knife for tornado
    knifeCount = 0;
    for (int i = 0; i < MAX_KNIVES; i++)
    {
        knives[i] = nullptr;
    }

    BossGamakichi = nullptr;


}

game::~game()
{
    // check to see ke leaderboard exist karta bhi hai ya nhi. 
    // if not exist avoid error by deleting
    
    for (int i = 0; i < 15; i++)
    {
        if (enemies[i] != nullptr)
        {
            delete enemies[i];
            enemies[i] = nullptr;
        }
    }
    enemyCount = 0;

    for (int i = 0; i < MAX_KNIVES; i++)
    {
        if (knives[i] != nullptr)
        {
            delete knives[i];
            knives[i] = nullptr;
        }
    }

    if (leaderboard != 0)   
    {
        delete leaderboard;
    }

    if (fileManager != 0)
    {
        delete fileManager;
    }
    if (pauseScreen != 0)
    {
        delete pauseScreen;
    }

    if (authManager != nullptr)
    {
        delete authManager;
        authManager = nullptr;
    }
    if (loginScreen != nullptr)
    {
        delete loginScreen;
        loginScreen = nullptr;
    }

    //Shop memory free
    delete shopScreen;
    shopScreen = nullptr;
}

void game::Run()
{
    Menu mainMenu(window);

    while (window.isOpen())
    {
        float deltaTime = clock.restart().asSeconds();

        //EVENT LOOP 
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();

            if (event->is<sf::Event::KeyPressed>() && currentState != LOGIN)
            {
                auto key = event->getIf<sf::Event::KeyPressed>();

                // SHOOT
                if (key && key->code == sf::Keyboard::Key::F)
                {
                    B1.shoot(
                        player1.getBounds().position.x,
                        player1.getBounds().position.y,
                        player1.getDirection()
                    );
                }
                if (key && key->code == sf::Keyboard::Key::RShift)
                {
                    B2.shoot(
                        player2.getBounds().position.x,
                        player2.getBounds().position.y,
                        player2.getDirection()
                    );
                }

                // HITBOX TOGGLE
                if (key && key->code == sf::Keyboard::Key::H)
                    Hitbox = !Hitbox;

                if (key && key->code == sf::Keyboard::Key::J)
                    EnemyHitbox = !EnemyHitbox;

                // ESCAPE
                if (key && key->code == sf::Keyboard::Key::Escape)
                {
                    if (currentState == GAME_OVER)
                    {
                        lives1 = 3;
                        lives2 = 3;
                        score1 = 0;
                        score2 = 0;
                        gems1.reset();
                        gems2.reset();
                        currentLevel = 1;
                        gameOverPrinted = false;
                        winPrinted = false;
                        loadLevel(1);
                        currentState = MENU;
                    }
                    else if (currentState == PLAYING)
                    {
                        currentState = PAUSED;
                        pauseScreen->show();
                        pauseScreen->resetBool();
                    }
                }

                
                if (key && key->code == sf::Keyboard::Key::Enter)
                {
                    if (currentState == LEVEL_COMPLETE)
                    {
                        currentLevel++;
                        if (currentLevel <= 10)
                        {
                            loadLevel(currentLevel);
                            winPrinted = false;
                            currentState = PLAYING;
                        }
                        else
                        {
                            winPrinted = true;
                            currentState = GAME_OVER;
                        }
                    }
                    else if (currentState == MENU)
                    {
                        int selected = mainMenu.getSelectedIndex();

                        if (selected == 0)
                        {
                            // New Game
                            lives1 = 3;
                            lives2 = 3;
                            score1 = 0;
                            score2 = 0;
                            gems1.reset();
                            gems2.reset();
                            currentLevel = 1;
                            winPrinted = false;
                            gameOverPrinted = false;
                            loadLevel(1);
                            currentState = PLAYING;
                        }
                        else if (selected == 1)  // Continue
                        {
                            SaveData saveData;
                            if (fileManager->loadGameData(playerName1, &saveData)
                                && saveData.currentLevel > 1)
                            {
                                currentLevel = saveData.currentLevel;
                                score1 = saveData.totalScore;
                                lives1 = saveData.livesRemaining;
                                score2 = 0;
                                lives2 = 3;
                                gems1.reset();
                                gems2.reset();
                                winPrinted = false;
                                gameOverPrinted = false;
                                loadLevel(currentLevel);
                                currentState = PLAYING;
                            }
                        }
                        else if (selected == 2)
                        {
                            showLeaderboard();
                        }
                        else if (selected == 4)
                        {
                            window.close();
                        }
                    }
                }
            }
        }
       

        
        if (currentState == LOGIN)
        {
            loginScreen->handleInput();

            if (loginScreen->wasLoginSuccessful())
            {
                playerName1 = authManager->getUsername();
                fileManager->addUser(playerName1, "");
                currentState = MENU;
            }
        }
        else if (currentState == MENU)
        {
            input1.updatePlayer1();
            input2.updatePlayer2();
            mainMenu.handleInput();
        }
        else if (currentState == LEADER_BOARD)
        {
            leaderboard->handleInput();
        }
        else if (currentState == PAUSED)
        {
            pauseScreen->handleInput();
        }
        else if (currentState == SHOP)
        {
            shopScreen->handleInput();

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
            {
                currentState = PAUSED;
                pauseScreen->show();
                pauseScreen->resetBool();
            }
        }
        else
        {
            input1.updatePlayer1();
            input2.updatePlayer2();
        }

        //update
        if (currentState != LOGIN)
        {
            update(deltaTime);
            B1.update(deltaTime);
            B2.update(deltaTime);
        }

        // rendering
        window.clear(sf::Color::Black);

        if (currentState == LOGIN)
        {
            loginScreen->draw();
        }
        else if (currentState == MENU)
        {
            mainMenu.draw();
        }
        else if (currentState == PLAYING)
        {
            window.draw(bgSprite);

            if (showLevelText)
            {
                levelDisplayTimer -= deltaTime;
                if (levelDisplayTimer <= 0)
                    showLevelText = false;
            }

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

            for (int i = 0; i < coinCount; i++)
                if (coinActive[i])
                    window.draw(coins[i]);

            player1.draw(window);
            player2.draw(window);

            for (int i = 0; i < enemyCount; i++)
                if (enemies[i] != nullptr && enemies[i]->isAlive())
                    enemies[i]->draw(window);

            B1.draw(window);
            B2.draw(window);


            // draw the knives that are thrown. or active
            for (int i = 0; i < MAX_KNIVES; i++)
            {
                if (knives[i] != nullptr && knives[i]->getActive())
                {
                    knives[i]->draw(window);
                }
            }

            window.draw(scoreText1);
            window.draw(scoreText2);
            window.draw(gemText1);
            window.draw(gemText2);

            if (Hitbox)
            {
                player1.drawHitbox(window);
                player2.drawHitbox(window);
            }
            if (EnemyHitbox)
            {
                for (int i = 0; i < enemyCount; i++)
                    if (enemies[i] != nullptr)
                        enemies[i]->drawHitbox(window);
            }

            window.draw(livesText1);
            window.draw(livesText2);

            if (isBossLevel)
            {
                window.draw(bossHealthBarBg);
                window.draw(bossHealthBarFill);
                window.draw(bossHealthText);
            }
        }
        else if (currentState == PAUSED)
        {
            window.draw(bgSprite);
            for (int i = 0; i < MAX_PLATFORMS; i++)
                platforms[i].draw(window);

            player1.draw(window);
            player2.draw(window);

            for (int i = 0; i < enemyCount; i++)
                if (enemies[i] != nullptr)
                    enemies[i]->draw(window);

            B1.draw(window);
            B2.draw(window);
            window.draw(scoreText1);
            window.draw(scoreText2);
            window.draw(livesText1);
            window.draw(livesText2);
            window.draw(gemText1);
            window.draw(gemText2);
            pauseScreen->draw();
        }
        else if (currentState == LEADER_BOARD)
        {
            leaderboard->draw();
            if (!leaderboard->getIsVisible())
            {
                currentState = MENU;
                leaderboard->show();
            }
        }
        else if (currentState == SHOP)
        {
            window.draw(bgSprite);
            for (int i = 0; i < MAX_PLATFORMS; i++)
                platforms[i].draw(window);
            player1.draw(window);
            player2.draw(window);
            window.draw(scoreText1);
            window.draw(scoreText2);
            window.draw(gemText1);
            window.draw(gemText2);
            window.draw(livesText1);
            window.draw(livesText2);
            shopScreen->draw();
         }
        else if (currentState == LEVEL_COMPLETE)
        {
            window.draw(levelCompleteText);
            window.draw(levelCompleteText2);
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

void game::update(float deltaTime)
{
   
    if (currentState == SHOP)
    {
        if (shopScreen->wasPurchased())
        {
            int idx = shopScreen->lastPurchasedIndex();
            if (idx == 0)  // Extra Life
            {
                if (activePlayer == 0) lives1++;
                else                   lives2++;
            }
            shopScreen->resetPurchaseFlag();
        }
        return;
    }
    if (currentState == PAUSED)
    {
        //resume
        if (pauseScreen->Resume())
        {
            currentState = PLAYING;
            pauseScreen->resetBool();
            clock.restart();
        }
        else if (pauseScreen->Shop())
        {
            activePlayer = 0;  // or add logic to pick P1 vs P2
            shopScreen->setActivePlayer(activePlayer);
            currentState = SHOP;
            pauseScreen->resetBool();
        }
        // quit to main menu
        else if (pauseScreen->Quit())
        {
            // Reset full game state so Menu starts fresh
            lives1 = 3;
            lives2 = 3;
            score1 = 0;
            score2 = 0;
            gems1.reset();
            gems2.reset();
            currentLevel = 1;
            winPrinted = false;
            gameOverPrinted = false;
            loadLevel(1);

            pauseScreen->resetBool();
            clock.restart();
            currentState = MENU;
        }
        // logout
        else if (pauseScreen->Logout())
        {
            // Reset full game state
            lives1 = 3;
            lives2 = 3;
            score1 = 0;
            score2 = 0;
            gems1.reset();
            gems2.reset();
            currentLevel = 1;
            winPrinted = false;
            gameOverPrinted = false;
            loadLevel(1);

            
            playerName1 = "";
            playerName2 = "";

            // Reset login screen so it is ready for a new login
            loginScreen->reset();   

            pauseScreen->resetBool();
            clock.restart();
            currentState = LOGIN;
        }

        return;   // stop all other update logic while paused
    }
    if (currentState == PLAYING)
    {
        
        
        if (deltaTime > 0.5f)
        {
            deltaTime = 0.5f;
        }
        if (invincibleTimer1 > 0)
            invincibleTimer1 -= deltaTime;
    
        if (invincibleTimer2 > 0) 
            invincibleTimer2 -= deltaTime;
        

        player1.update(input1, platforms, MAX_PLATFORMS);
        player2.update(input2, platforms, MAX_PLATFORMS);
   

        for (int i = 0; i < enemyCount; i++)
        {
          
            if (enemies[i] != nullptr)
            {
                enemies[i]->updateMovement(deltaTime, platforms, MAX_PLATFORMS);
               
            }
        }

        // if level is 5 then we start updating mogera
        
        if (currentLevel == 5)
        {
            for (int i = 0; i < enemyCount; i++)
            {
                if (enemies[i] == nullptr)
                {
                    continue;
                }

                if (currentLevel == 5 && BossMogera != nullptr && BossMogera->isAlive())
                {
                    BossMogera->updatePhase(deltaTime);
                    spawnMogeraChildren();
                    updateBossHealthBar();
                }
                
            }
                
        }


       // get player  position to pass to Gamakichi for rocket aiming
        if (currentLevel == 10 && BossGamakichi != nullptr && BossGamakichi->isAlive())
        {
            float p1x = player1.getBounds().position.x;
            float p1y = player1.getBounds().position.y;
            if (rand() % 2 == 0)
            {
                p1x = player2.getBounds().position.x;
                p1y = player2.getBounds().position.y;
            }
            

            //  pass player position so rockets aim correctly like knives of tornado
            BossGamakichi->lastPlayerX = p1x;
            BossGamakichi->lastPlayerY = p1y;

            BossGamakichi->updatePhase(deltaTime);
            spawnGamakichiChildren();
            updateGamakichiBossHealthBar();

            // check if rocket collided with player
            GamakichiRocket** rockets = BossGamakichi->getRockets();
            int rocketCount = BossGamakichi->getRocketCount();

            for (int r = 0; r < rocketCount; r++)
            {
                if (rockets[r] == nullptr || !rockets[r]->getActive())
                {
                    continue;
                }

                // if rocket hit player 1
                if (rockets[r]->hasExploded())
                {
                    if (lives1 > 0 && invincibleTimer1 <= 0 &&
                        player1.getBounds().findIntersection(rockets[r]->getExplosionBounds()))
                    {
                        lives1--;
                        invincibleTimer1 = 1;
                        if (lives1 > 0)
                        {
                            player1.Reset();
                        }
                    }

                    // if rocket hit player  2. else if nhi hai cos explosion can affect both
                    if (lives2 > 0 && invincibleTimer2 <= 0 &&
                        player2.getBounds().findIntersection(rockets[r]->getExplosionBounds()))
                    {
                        lives2--;
                        invincibleTimer2 = 1;
                        if (lives2 > 0)
                        {
                            player2.Reset();
                        }
                    }
                }
                else
                {
                    // direct hit of rocket with the players checking
                    if (lives1 > 0 && invincibleTimer1 <= 0 &&
                        player1.getBounds().findIntersection(rockets[r]->getBounds()))
                    {
                        lives1--;
                        invincibleTimer1 = 1;
                        rockets[r]->markAsHit();
                        if (lives1 > 0)
                        {
                            player1.Reset();
                        }
                    }

                    
                    if (lives2 > 0 && invincibleTimer2 <= 0 &&
                        player2.getBounds().findIntersection(rockets[r]->getBounds()))
                    {
                        lives2--;
                        invincibleTimer2 = 1;
                        rockets[r]->markAsHit();
                        if (lives2 > 0)
                        {
                            player2.Reset();
                        }
                    }
                }
            }
        }

        // make the enemies who are tornado throw knife
        for (int i = 0; i < enemyCount; i++)
        {
            if (enemies[i] == nullptr || !enemies[i]->isAlive())
            {
                continue;
            }

            
            Tornado* tornado = dynamic_cast<Tornado*>(enemies[i]);
            if (tornado != nullptr && tornado->canThrow())
            {
                float targetX = player1.getBounds().position.x;
                float targetY = player1.getBounds().position.y;
                if (rand() % 2 == 0)
                {
                    targetX = player2.getBounds().position.x;
                    targetY = player2.getBounds().position.y;
                }
                

                // check if knife slot is empty
                for (int k = 0; k < MAX_KNIVES; k++)
                {
                    if (knives[k] == nullptr || !knives[k]->getActive())
                    {
                        /// delete old knife to avoid memory leaks
                        if (knives[k] != nullptr)
                        {
                            delete knives[k];
                        }
                        
                        //create knife in tornado class
                        knives[k] = tornado->createKnife(targetX, targetY);
                        break;
                    }
                }
            }
        }
        //eachfram knife updated
        updateKnives(deltaTime);
        checkKnifePlayerCollisions();

       
        for (int i = 0; i < enemyCount; i++)
        {
            if (enemies[i] == nullptr || !enemies[i]->isAlive())
            {
                continue;
            }

            // modify add clock to prevent multiple collision at an instance 
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
                invincibleTimer2 = 1;

                if (lives2 > 0)
                {
                    player2.Reset();
                }
            }
        }


        

        for (int i = 0; i < enemyCount; i++)
        {
            if (enemies[i] == nullptr || !enemies[i]->isAlive())
            {
                continue;
            }
            if (enemies[i]->isAlive() &&
                B1.checkactive() &&
                B1.getbounds().findIntersection(enemies[i]->getBounds()))
            {
                enemies[i]->onHit();

                if (!enemies[i]->isAlive())
                {
                    // modify create enemy . get score and return rand values
                    score1 += 100;
                    // give gem
                    int gemDrop = 1 + rand() % 5;
                    gems1.addGems(gemDrop);
                }

                B1 = Ball();
            }
        }

        

        for (int i = 0; i < enemyCount; i++)
        {
            if (enemies[i] == nullptr || !enemies[i]->isAlive())
            {
                continue;
            }
            if (enemies[i]->isAlive() &&
                B2.checkactive() &&
                B2.getbounds().findIntersection(enemies[i]->getBounds()))
            {
                enemies[i]->onHit();

                if (!enemies[i]->isAlive())
                {
                    // modify getrand score
                    score2 += 100;
               
                    gems2.addGems(1 + rand() % 5);
                }

                B2 = Ball();
            }
        }
       
        // ball collison with 2nd boss detect and get reqarded per shot
        if (currentLevel == 10 && BossGamakichi != nullptr && BossGamakichi->isAlive())
        {
            if (B1.checkactive() && B1.getbounds().findIntersection(BossGamakichi->getBounds()))
            {
                BossGamakichi->onHit();
                score1 += 1500;
                gems1.addGems(3 + rand() % 5);
                B1 = Ball();
            }

            if (B2.checkactive() && B2.getbounds().findIntersection(BossGamakichi->getBounds()))
            {
                BossGamakichi->onHit();
                score2 += 1500;
                gems2.addGems(3 + rand() % 5);
                B2 = Ball();
            }
        }

        scoreText1.setString("P1: " + to_string(score1));
        scoreText2.setString("P2: " + to_string(score2));
        livesText1.setString("P1 Lives: " + std::to_string(lives1));
        livesText2.setString("P2 Lives: " + std::to_string(lives2));
    }

  
    if (currentState == PLAYING && AllDead() && !winPrinted)
    {
        winPrinted = true;
        currentState = LEVEL_COMPLETE;
        submitScores();
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
            gems1.addGems(CointoGemValue);
        }

        if (coinActive[i] &&
            player2.getBounds().findIntersection(coins[i].getGlobalBounds()))
        {
            coinActive[i] = false;
            score2 += 50;
            gems2.addGems(CointoGemValue);
        }
    }

    UpdatescoreUI();
}

void game::UpdatescoreUI() {
    scoreText1.setString("P1: " + std::to_string(score1));
    scoreText2.setString("P2: " + std::to_string(score2));

    gemText1.setString("Gems: " + std::to_string(gems1.getGems()));
    gemText2.setString("Gems: " + std::to_string(gems2.getGems()));

}

//level functions
void game::loadLevel(int level)
{
    // clean enemy pointers before each level
    for (int i = 0; i < 15; i++)
    {
        if (enemies[i] != nullptr)
        {
            delete enemies[i];
            enemies[i] = nullptr;
        }
    }
    enemyCount = 0;
    BossMogera = nullptr;
    BossGamakichi = nullptr;
    isBossLevel = false;
    coinCount = 0;

    for (int i = 0; i < MAX_KNIVES; i++)
    {
        if (knives[i] != nullptr)
        {
            delete knives[i];
            knives[i] = nullptr;
        }
    }
    

    if (level == 1)
    {
        if (!bgTexture.loadFromFile("./level1.png.png"))
            cout << "Background not loading\n";
        else
        {
            bgSprite = sf::Sprite(bgTexture);
            bgSprite.setTexture(bgTexture);
            bgSprite.setScale({ 800.0f / bgTexture.getSize().x, 600.0f / bgTexture.getSize().y });
        }

        enemyCount = 2;
        enemies[0] = new Boton(520, 100);
        enemies[1] = new Fooga(20, 280);
        

        platformCount = 5;
        platforms[0] = platform(0, 550, 800, 50);
        platforms[1] = platform(50, 400, 200, 20);
        platforms[2] = platform(400, 300, 200, 20);
        platforms[3] = platform(300, 200, 200, 20);
        platforms[4] = platform(400, 420, 200, 20);

        levelText.setString("Level 1");
        levelDisplayTimer = 2.0f;
        showLevelText = true;
        return;
    }

    if (level == 2)
    {
        enemyCount = 3;
        enemies[0] = new Boton(100, 300);
        enemies[1] = new Boton(400, 200);
        enemies[2] = new Fooga(200, 100);

        platformCount = 5;
        platforms[0] = platform(0, 550, 800, 50);
        platforms[1] = platform(0, 450, 300, 20);
        platforms[2] = platform(500, 350, 300, 20);
        platforms[3] = platform(200, 250, 200, 20);
        platforms[4] = platform(400, 420, 200, 20);
  

        levelText.setString("Level 2");
        levelDisplayTimer = 2.0f;
        showLevelText = true;
        return;
    }

    if (level == 3)
    {
        enemyCount = 4;
        enemies[0] = new Boton(100, 400);
        enemies[1] = new Boton(300, 460);
        enemies[2] = new Fooga(200, 150);
        enemies[3] = new Tornado(500, 350);

        platformCount = 5;
        platforms[0] = platform(0, 550, 800, 50);
        platforms[1] = platform(100, 450, 200, 20);
        platforms[2] = platform(400, 450, 200, 20);
        platforms[3] = platform(250, 300, 200, 20);
        platforms[4] = platform(150, 150, 150, 20);

        levelText.setString("Level 3");
        levelDisplayTimer = 2.0f;
        showLevelText = true;
        return;
    }

    if (level == 5)
    {
        isBossLevel = true;

        BossMogera = new Mogera(360, 200);
        enemies[0] = BossMogera;
        enemyCount = 1;

        platformCount = 3;
        platforms[0] = platform(0, 550, 800, 50);
        platforms[1] = platform(50, 380, 300, 20);
        platforms[2] = platform(450, 380, 300, 20);

        levelText.setString("LEVEL 5: MOGERA BOSS!");
        levelDisplayTimer = 2;
        showLevelText = true;
        return;
    }

    //final boss finally!
    if (level == 10)
    {
        isBossLevel = true;

        // Center top of screen jese mogera tha
        BossGamakichi = new Gamakichi(220, 100);
        enemies[0] = BossGamakichi;
        enemyCount = 1;

        platformCount = 5;
        platforms[0] = platform(0, 550, 800, 50);
        platforms[1] = platform(50, 430, 200, 20);
        platforms[2] = platform(300, 330, 200, 20);
        platforms[3] = platform(550, 430, 200, 20);
        platforms[4] = platform(150, 230, 500, 20);

        levelText.setString("LEVEL 10: GENICHIRO FINAL BOSS!");
        levelDisplayTimer = 3;
        showLevelText = true;
        return;
    }

    //Bonus levels

    if (level == 4 || level == 9)
    {
        platformCount = 3;
        platforms[0] = platform(0, 550, 800, 50);
        platforms[1] = platform(100, 400, 200, 20);
        platforms[2] = platform(400, 300, 200, 20);

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

    // generic levels 6,7,8

    platformCount = 5;
    platforms[0] = platform(0, 550, 800, 50);
    platforms[1] = platform(50, 450, 200, 20);
    platforms[2] = platform(550, 400, 200, 20);
    platforms[3] = platform(250, 300, 300, 20);
    platforms[4] = platform(150, 180, 200, 20);

    enemyCount = level + 1;
    if (enemyCount > 10) enemyCount = 10;

    for (int i = 0; i < enemyCount; i++)
    {
        int pIndex = (i % (platformCount - 1)) + 1;

        sf::Vector2f pPos = platforms[pIndex].getBody().getPosition();
        sf::Vector2f pSize = platforms[pIndex].getBody().getSize();

        float x = pPos.x + (i * 40) % int(pSize.x - 40);
        float y = pPos.y - 40;

        if (i % 3 == 2 && level >= 6)
        {
            enemies[i] = new Tornado(x, y);
        }
        else if (i % 2 == 0)
            enemies[i] = new Boton(x, y);
        else
            enemies[i] = new Fooga(x, y);

        float speedBoost = 0.001f * level;
        enemies[i]->setSpeed(enemies[i]->getSpeed() + speedBoost);
    }

    levelText.setString("Level " + std::to_string(level));
    levelDisplayTimer = 2;
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
        if (enemies[i] != nullptr && enemies[i]->isAlive())
        {
            return false;
        }
    }

    return true;
}


// Submit both player scores to the database when both players die
void game::submitScores()
{
    
   
    if (!playerName1.empty())
    {
        SaveData data;
        data.username = playerName1;
        //data.currentLevel = currentLevel;
        data.currentLevel = currentLevel + 1;
        data.totalScore = score1;
        data.totalGems = gems1.getGems();
        data.livesRemaining = lives1;
        data.characterSelected = 0;

        fileManager->saveGameData(playerName1, &data);
        fileManager->addScore(playerName1, score1);
    }

    if (!playerName2.empty())
    {
        fileManager->addScore(playerName2, score2);
    }

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


void game::spawnMogeraChildren()
{
    if (BossMogera != nullptr && BossMogera->getCanSpawnChild() && BossMogera->isAlive())
    {
        // modify so that when moger child goes off screen or is hit by a ball it is destroyed and new mob spawn
        // find free slot in the child reserved zone

        BossMogera->setCanSpawnChild(false);
        for (int slot = 8; slot < 15; slot++)
        {
            if (enemies[slot] == nullptr || !enemies[slot]->isAlive())
            {
                
                if (enemies[slot] != nullptr) 
                {
                    delete enemies[slot];
                }

                int dir = -1;
                if (rand() % 2 == 0)
                {
                    dir = 1;
                }

                float cx = BossMogera->getX();
                if (dir == 1)
                {
                    cx += BossMogera->getWidth() + 5;
                }
                else
                {
                    cx -= 30;
                }
                float cy = BossMogera->getY();

                enemies[slot] = new MogeraChild(cx, cy, dir);

                if (slot >= enemyCount)
                {
                    enemyCount = slot + 1;
                }

                break;
            }
        }
        BossMogera->setCanSpawnChild(false);
    }
}

void game::updateBossHealthBar()
{
    if (!isBossLevel || BossMogera == nullptr)
    {
        bossHealthBarFill.setSize(sf::Vector2f(0, 18));
        return;
    }

    if (BossMogera->isAlive())
    {
        int maxHp = 30;
        // type cast to float bcz reounding off to int produce uneven fractiion
        float fraction = (float)BossMogera->getHealth() / (float)maxHp;

        if (fraction < 0)
        {
            fraction = 0;
        }

        bossHealthBarFill.setSize(sf::Vector2f(300.f * fraction, 18)); // X size will reduce
    }
    else
    {
        // boss dead then no health
        bossHealthBarFill.setSize(sf::Vector2f(0, 18));
    }
}


void game::spawnGamakichiChildren()
{
    if (BossGamakichi != nullptr && BossGamakichi->getCanSpawnChild() && BossGamakichi->isAlive())
    {
        BossGamakichi->setCanSpawnChild(false);

        // same as mogera
        for (int slot = 8; slot < 15; slot++)
        {
            if (enemies[slot] == nullptr || !enemies[slot]->isAlive())
            {
                if (enemies[slot] != nullptr)
                {
                    delete enemies[slot];
                }

                // spawning 
                float cx = BossGamakichi->getX() + (rand() % 200) - 100;
                float cy = BossGamakichi->getY();

                // clamp spawn x so child will not spawn off screen
                if (cx < 10)
                {
                    cx = 10;
                }
                if (cx > 750) 
                {
                    cx = 750;
                }

                enemies[slot] = new Boton(cx, cy);

                if (slot >= enemyCount)
                {
                    enemyCount = slot + 1;
                }

                break;
            }
        }
    }
}


void game::updateGamakichiBossHealthBar()
{
    if (!isBossLevel || BossGamakichi == nullptr)
    {
        bossHealthBarFill.setSize(sf::Vector2f(0, 18));
        return;
    }

    if (BossGamakichi->isAlive())
    {
        int maxHp = 60;    
        float fraction = (float)BossGamakichi->getHealth() / (float)maxHp;

        if (fraction < 0)
        {
            fraction = 0;
        }

        bossHealthBarFill.setSize(sf::Vector2f(300.f * fraction, 18));
    }
    else
    {
        bossHealthBarFill.setSize(sf::Vector2f(0, 18));
    }
}


void game::updateKnives(float deltaTime)
{
    for (int i = 0; i < MAX_KNIVES; i++)
    {
        if (knives[i] == nullptr)
        {
            continue;
        }

        if (knives[i]->getActive())
        {
            knives[i]->updatePosition(deltaTime);
        }
        else
        {
            // knife went off screen or hit something (basically deactive hai). so we free memory
            delete knives[i];
            knives[i] = nullptr;
        }
    }
}


void game::checkKnifePlayerCollisions()
{
    for (int i = 0; i < MAX_KNIVES; i++)
    {
        if (knives[i] == nullptr || !knives[i]->getActive())
        {
            continue;
        }

        //  knife hit player1
        if (lives1 > 0 && invincibleTimer1 <= 0 && player1.getBounds().findIntersection(knives[i]->getBounds()))
        {
            lives1--;
            invincibleTimer1 = 1.0f;
            knives[i]->markAsHit();   //  deactivate knife on hit

            if (lives1 > 0)
            {
                player1.Reset();
            }
        }

        //  knife hit player2 . we check active again ke knife player 1 go hit na kiya ho and deactive hogai ho
        if (knives[i] != nullptr && knives[i]->getActive() && lives2 > 0 && invincibleTimer2 <= 0 &&
            player2.getBounds().findIntersection(knives[i]->getBounds()))
        {
            lives2--;
            invincibleTimer2 = 1.0f;
            knives[i]->markAsHit();   

            if (lives2 > 0)
            {
                player2.Reset();
            }
        }
    }
}