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
    // no default constructora as when u have (sf::RenderWindow&). if no window then noway for SFML output
    Menu(sf::RenderWindow& gameWindow, bool pausesGame = true);

    int getSelectedIndex() const;
    

    virtual ~Menu();

    virtual void draw();

    virtual void handleInput();

    void updateMenuColors();
 
};