#include "Pause.h"

// Constructor initializes pause screen
PauseScreen::PauseScreen(sf::RenderWindow& gameWindow)
    : Display(true), window(gameWindow), titleText(font)
{
    selected = 0;
    shouldResume = false;
    shouldQuit = false;

    font.openFromFile("RussoOne-Regular.ttf");
    
    for (int i = 0; i < 5; i++)
    {
        menuItems[i] = new sf::Text(font);
        menuItems[i]->setFont(font);
    }

   
    
    // Setup title
    titleText.setFont(font);
    titleText.setString("PAUSED");
    titleText.setCharacterSize(48);
    titleText.setFillColor(sf::Color::White);
    titleText.setPosition(sf::Vector2f(300, 100));

    // Setup menu items
    string options[5] = { "Resume","Save Game", "Open Shop", "Log Out", "Quit to Menu" };

    for (int i = 0; i < 5; i++)
    {
        menuItems[i]->setFont(font);
        menuItems[i]->setString(options[i]);
        menuItems[i]->setCharacterSize(28);
        menuItems[i]->setPosition(sf::Vector2f(280, 220 + i * 60));
    }

    updateMenuColors();
}

PauseScreen::~PauseScreen()
{
    for (int i = 0; i < 5; i++)
    {
       delete menuItems[i];
    }
}


void PauseScreen::draw()
{
    // visible helps me to alter between different types of screens
    if (!isVisible) 
    {
        return;
    }

    // Draw semi transparent background overlay
    sf::RectangleShape overlay(sf::Vector2f(800, 600));
    overlay.setFillColor(sf::Color(0, 0, 0, 128)); //0 0 0 is black. 128 is alpha factor for pause

    window.draw(overlay);   // overlay pehlay and iss ke upar text
    window.draw(titleText);

    for (int i = 0; i < 4; i++)
    {
        window.draw(*menuItems[i]);
    }
}

void PauseScreen::handleInput()
{
    if (!isVisible)
    {
        return;
    }

    static sf::Clock inputTimer;

    if (inputTimer.getElapsedTime().asMilliseconds() < 300)
    {
        return;
    }

    // Up arrow or W to move up
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
    {
        if (selected > 0)
        {
            selected--;
        }
        else
        {
            selected = 3;
        }
        updateMenuColors();
        inputTimer.restart();
    }

    // Down arrow or S to move down
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
    {
        if (selected < 3)
        {
            selected++;
        }
        else
        {
            selected = 0; 
        }
        updateMenuColors();
        inputTimer.restart();
    }

    //selected option 
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter))
    {
        if (selected == 0)
        {
            // Resume
            shouldResume = true;
            hide();
        }
        else if (selected == 1)
        {
            // save game modify
            
        }
        else if (selected == 2)
        {
            // modify open shop
        }
        else if (selected == 3)
        {
            // modify Logout
        }
        else if (selected == 4)
        {
            // Quit to menu
            shouldQuit = true;
            hide();
        }

        inputTimer.restart();
    }

}

// Returns whether resume was selected
bool PauseScreen::Resume()
{
    return shouldResume;
}


bool PauseScreen::Quit()
{
    return shouldQuit;
}


void PauseScreen::resetBool()
{
    shouldResume = false;
    shouldQuit = false;
}


void PauseScreen::updateMenuColors()
{
    for (int i = 0; i < 4; i++)
    {
        if (i == selected)
        {
            menuItems[i]->setFillColor(sf::Color::Yellow); 
        }
        else
        {
            menuItems[i]->setFillColor(sf::Color::White); // default color
        }
    }
}