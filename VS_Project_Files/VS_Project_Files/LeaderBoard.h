#pragma once
#include <string>
#include "Display.h"
#include "DatabaseManagement.h"
#include <SFML/Graphics.hpp>
using namespace std;

// Leaderboard screen — displays top 10 scores
class LeaderboardScreen : public Display
{
private:
    sf::RenderWindow& window;       // reference to game window
    FileManage* fileManager;        // reference to file/score system (not owned)

    sf::Font font;
    sf::Text titleText;
    sf::Text entryTexts[10];        // one text per leaderboard entry
    sf::Text backButton;

    string leaderboardNames[10];    // top-10 usernames
    int    leaderboardScores[10];   // top-10 scores

public:
    LeaderboardScreen(sf::RenderWindow& gameWindow, FileManage* fm);
    ~LeaderboardScreen() override;

    void draw() override;
    void handleInput() override;

    // Reload data from database and refresh display
    void refreshLeaderboard();

private:
    void updateDisplay();
};