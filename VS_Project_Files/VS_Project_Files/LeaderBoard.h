#pragma once
#include <string>
#include "Display.h"
#include "DatabaseManagement.h"
#include <SFML/Graphics.hpp>
using namespace std;

class LeaderboardScreen : public Display
{
private:
    sf::RenderWindow& window;
    FileManage* fileManager;

    // Fonts
    sf::Font font;

    // Background panel
    sf::RectangleShape bgPanel;
    sf::RectangleShape headerBar;

    // Title
    sf::Text titleText;

    // Column headers
    sf::Text colRank;
    sf::Text colName;
    sf::Text colScore;

    // Separator lines
    sf::RectangleShape headerSep;        // under column headers
    sf::RectangleShape accentLine;       // decorative line under title

    // Per-entry widgets (10 rows)
    sf::Text* RanksTexts[10];       // rank number
    sf::Text* nameTexts[10];        // player name
    sf::Text* scoreTexts[10];       // score
    sf::RectangleShape* rowBgs[10];           // row highlight bg
    sf::CircleShape* rankBadges[10];       // circular badge behind rank number

    // Footer
    sf::Text back;
    sf::RectangleShape footerLine;

    // Data
    string leaderboardUserNames[10];
    int    leaderboardScores[10];

    // Helpers
    sf::Color getRankColor(int rank) const;      // gold/silver/bronze/normal
    sf::Color getRankBadgeColor(int rank) const;
    void buildRow(int i);

public:
    LeaderboardScreen(sf::RenderWindow& gameWindow, FileManage* fm);
    ~LeaderboardScreen() override;

    void draw()         override;
    void handleInput()  override;
    void updateLeaderboard();
};