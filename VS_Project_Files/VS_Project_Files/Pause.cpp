#include "Pause.h"

static const int MENU_COUNT = 5;



PauseScreen::PauseScreen(sf::RenderWindow& gameWindow)
    : Display(true), window(gameWindow), titleText(font)
{
    selected = 0;
    shouldResume = false;
    shouldQuit = false;
    shouldLogout = false;
    shouldShop = false;   

    font.openFromFile("RussoOne-Regular.ttf");

    for (int i = 0; i < MENU_COUNT; i++)
        menuItems[i] = new sf::Text(font);

    // Title
    titleText.setFont(font);
    titleText.setString("PAUSED");
    titleText.setCharacterSize(48);
    titleText.setFillColor(sf::Color::White);
    sf::FloatRect tb = titleText.getLocalBounds();
    titleText.setOrigin(sf::Vector2f(tb.size.x / 2.f, tb.size.y / 2.f));
    titleText.setPosition(sf::Vector2f(400.f, 120.f));

    // Menu options
    string options[MENU_COUNT] = { "Resume", "Save Game", "Open Shop", "Log Out", "Quit to Menu" };
    for (int i = 0; i < MENU_COUNT; i++)
    {
        menuItems[i]->setFont(font);
        menuItems[i]->setString(options[i]);
        menuItems[i]->setCharacterSize(28);
        sf::FloatRect b = menuItems[i]->getLocalBounds();
        menuItems[i]->setOrigin(sf::Vector2f(b.size.x / 2.f, 0.f));
        menuItems[i]->setPosition(sf::Vector2f(400.f, 210.f + i * 58.f));
    }

    updateMenuColors();
}



PauseScreen::~PauseScreen()
{
    for (int i = 0; i < MENU_COUNT; i++)
    {
        delete menuItems[i];
        menuItems[i] = nullptr;
    }
}



void PauseScreen::draw()
{
    if (!isVisible) return;

    sf::RectangleShape overlay(sf::Vector2f(800.f, 600.f));
    overlay.setFillColor(sf::Color(0, 0, 0, 160));
    window.draw(overlay);

    window.draw(titleText);

    for (int i = 0; i < MENU_COUNT; i++)
        window.draw(*menuItems[i]);
}



void PauseScreen::handleInput()
{
    if (!isVisible) return;

    static sf::Clock inputTimer;
    if (inputTimer.getElapsedTime().asMilliseconds() < 300)
        return;

    // Navigate up
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
    {
        selected = (selected == 0) ? MENU_COUNT - 1 : selected - 1;
        updateMenuColors();
        inputTimer.restart();
        return;
    }

    // Navigate down
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
    {
        selected = (selected == MENU_COUNT - 1) ? 0 : selected + 1;
        updateMenuColors();
        inputTimer.restart();
        return;
    }

    // Confirm selection
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter))
    {
        switch (selected)
        {
        case 0:   // Resume
            shouldResume = true;
            hide();
            break;

        case 1:  
            break;

        case 2:  
            shouldShop = true;
            hide();
            break;

        case 3:   // Log Out
            shouldLogout = true;
            hide();
            break;

        case 4:   // Quit to Menu
            shouldQuit = true;
            hide();
            break;
        }
        inputTimer.restart();
    }
}



bool PauseScreen::Resume() { return shouldResume; }
bool PauseScreen::Quit() { return shouldQuit; }
bool PauseScreen::Logout() { return shouldLogout; }
bool PauseScreen::Shop() { return shouldShop; }  



void PauseScreen::resetBool()
{
    shouldResume = false;
    shouldQuit = false;
    shouldLogout = false;
    shouldShop = false;   
}



void PauseScreen::updateMenuColors()
{
    for (int i = 0; i < MENU_COUNT; i++)
    {
        if (i == selected)
        {
            menuItems[i]->setFillColor(sf::Color::Yellow);
            menuItems[i]->setCharacterSize(30);
        }
        else
        {
            menuItems[i]->setFillColor(sf::Color::White);
            menuItems[i]->setCharacterSize(28);
        }
     
        sf::FloatRect b = menuItems[i]->getLocalBounds();
        menuItems[i]->setOrigin(sf::Vector2f(b.size.x / 2.f, 0.f));
    }
}