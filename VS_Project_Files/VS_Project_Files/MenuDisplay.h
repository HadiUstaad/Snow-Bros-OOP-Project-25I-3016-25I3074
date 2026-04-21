#pragma once
#include "Display.h"
#include "SFML/Graphics.hpp"
#include <string>

class Menu : public Display
{
    sf::RenderWindow& window;  // Reference to the main window for drawing and input
    int choice;
    

    sf::Font font;
    sf::Text titleText;

    static const int item = 5;
    sf::Text menuItems[item];

    
public:

    Menu(sf::RenderWindow& gameWindow, bool pausesGame = true);

    int getSelectedIndex() const;
    Menu();

    virtual ~Menu();

    virtual void draw();

    virtual void handleInput();

    // Helper methods for internal navigation
    void moveUp();
    void moveDown();
    void updateMenuColors();
 
};