#pragma once
#include "Display.h"
#include <SFML/Graphics.hpp>
using namespace std;

class PauseScreen : public Display
{
private:
    sf::RenderWindow& window;
    sf::Font          font;
    sf::Text          titleText;
    sf::Text* menuItems[5];   // Resume / Save / Shop / Log Out / Quit to Menu
    int               selected;

    bool shouldResume;
    bool shouldQuit;
    bool shouldLogout;
    bool shouldShop;      // ← fixed: was "shopSelected", never initialised or set

public:
    PauseScreen(sf::RenderWindow& gameWindow);
    ~PauseScreen() override;

    void draw()        override;
    void handleInput() override;

    bool Resume();
    bool Quit();
    bool Logout();
    bool Shop();

    void resetBool();
    void updateMenuColors();
};