#pragma once
#include <string>
#include "Display.h"
#include "DatabaseManagement.h"
#include <SFML/Graphics.hpp>
using namespace std;

// display top 10 scores
class LeaderboardScreen : public Display
{
private:
    sf::RenderWindow& window;       // reference to game window
    FileManage* fileManager;        // aggregation

    sf::Font font;
    sf::Text titleText;
    sf::Text* RanksTexts[10];        // one text per leaderboard entry
    sf::Text back;

    string leaderboardUserNames[10];    // usernames of the top 10 scorers
    int    leaderboardScores[10];   // top-10 scores

public:
    LeaderboardScreen(sf::RenderWindow& gameWindow, FileManage* fm);
    ~LeaderboardScreen() override;

    void draw() override;
    void handleInput() override;

    // Reload data from database and refresh display
    void updateLeaderboard();  
    

};