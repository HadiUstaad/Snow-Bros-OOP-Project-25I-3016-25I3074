#include "LeaderBoard.h"
#include <string>
#include <iostream>
using namespace std;

LeaderboardScreen::LeaderboardScreen(sf::RenderWindow& gameWindow, FileManage* fm)
    : Display(true), window(gameWindow), titleText(font), back(font)
{
    fileManager = fm;

    // this loads the font and checks if it is loaded
    if (!font.openFromFile("RussoOne-Regular.ttf"))
    {
        cout << "Error: Can not load font 'RussoOne-Regular.ttf'\n";
    }
    for (int i = 0; i < 10; i++)
    {
        RanksTexts[i] = new sf::Text(font);
        leaderboardUserNames[i] = "";
        leaderboardScores[i] = 0;
    }

    // Title
    titleText.setFont(font);
    titleText.setString("LEADERBOARD");
    titleText.setCharacterSize(36);
    titleText.setFillColor(sf::Color::White);
    titleText.setPosition(sf::Vector2f(260, 30));

    // Entry texts
    for (int i = 0; i < 10; i++)
    {
        RanksTexts[i]->setFont(font);
        RanksTexts[i]->setCharacterSize(18);
        RanksTexts[i]->setFillColor(sf::Color::Yellow);
        RanksTexts[i]->setPosition(sf::Vector2f(150, 100 + i * 40));
    }

    // Back button hint
    back.setFont(font);
    back.setString("Press ESC to go back");
    back.setCharacterSize(20);
    back.setFillColor(sf::Color::White);
    back.setPosition(sf::Vector2f(250, 540));

   updateLeaderboard();
}

LeaderboardScreen::~LeaderboardScreen()
{
}

void LeaderboardScreen::draw()
{
    // if visibility is off no point to display
    if (!isVisible)
    {
        return;
    }

    window.draw(titleText);

    for (int i = 0; i < 10; i++)
    {
        window.draw(*RanksTexts[i]);
    }

    window.draw(back);
}

void LeaderboardScreen::handleInput()
{
    if (!isVisible)
    {
        return;
    }

    static sf::Clock inputTimer; // static so clock keeps ticking
    if (inputTimer.getElapsedTime().asMilliseconds() < 300)
    {
        return;
    }

    // agar escape kardiya to ye menu hide hojai ga
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
    {
        isVisible = false;
        inputTimer.restart();
    }
}

void LeaderboardScreen::updateLeaderboard()
{
    fileManager->getTopScores(leaderboardUserNames, leaderboardScores);


    for (int i = 0; i < 10; i++)
    {
        
        string rank = to_string(i + 1);
        string name; 
        if (leaderboardUserNames[i].empty() == true)
        {
            name = "--- N/L ---";
        }
        else
        {
            name = leaderboardUserNames[i];
        }
        string score = to_string(leaderboardScores[i]);

        // modifiy to look better later
        string display = rank + ".  " + name + "   | " + score;
        RanksTexts[i]->setString(display);
    }
}

