#pragma once
#include "Display.h"
#include <SFML/Graphics.hpp>

using namespace std;




class PauseScreen : public Display
{
private:
    sf::RenderWindow& window;       // reference to game window

    sf::Font font;                  // font for text
    sf::Text titleText;             // pause title
    sf::Text* menuItems[5];          // menu options
    int selected;              // currently selected option

    bool shouldResume;              // flag to resume game
    bool shouldQuit;                // flag to quit game

public:

    PauseScreen(sf::RenderWindow& gameWindow);

    ~PauseScreen() override;

    void draw() override;

    void handleInput() override;

    bool Resume();             // check if resume selected
    bool Quit();               // check if quit selected
    void resetBool();              // reset action flags

    void updateMenuColors(); // have different menus. implement later modify
};