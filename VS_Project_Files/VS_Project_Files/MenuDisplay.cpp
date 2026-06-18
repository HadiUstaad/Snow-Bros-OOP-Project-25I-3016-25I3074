#include "MenuDisplay.h"
#include <iostream>
#include "SFML/Graphics.hpp"

using namespace std;

// in sfml 3 text doesnt have a default constructor and requires that we initialize it with font. as in classes the text is already made
// so we initialize it with font before executing constructors body
Menu::Menu(sf::RenderWindow& gameWindow, bool pausesGame) : Display(pausesGame), window(gameWindow) , titleText(font) 
, menuItems{sf::Text(font),sf::Text(font), sf::Text(font), sf::Text(font), sf::Text(font)} ,bgTexture(), bgSprite(bgTexture)
,selector(font, ">",30)
{
    // window = gameWindow; we cannot initialize here. it is a rule of renderwindow. we must initialize it before running 
    // the body of constructor

    choice = 0;
    if (!bgTexture.loadFromFile("./Menu.png.png"))
    {
        std::cout << "Error loading menu background\n";
    }


    bgSprite = sf::Sprite(bgTexture);
    bgSprite.setTexture(bgTexture);

    // scale to 800x600
    bgSprite.setScale(sf::Vector2f(
        800.0f / bgTexture.getSize().x,
        600.0f / bgTexture.getSize().y
    ));

    // font loads from openfromfiles. place all fonts in bin folder
    if (!font.openFromFile("RussoOne-Regular.ttf")) 
    {
        cout<< "Error: Can not load font 'RussoOne-Regular.ttf'\n";
    }

    // Set up tilte
    titleText.setFont(font);
    titleText.setString("SNOW BROS");
    titleText.setCharacterSize(50);
    titleText.setFillColor(sf::Color::White);
    titleText.setPosition(sf::Vector2f(220,120)); 
    selector.setFillColor(sf::Color::White);

    // created a seperated array bcz it will help us to make a for loop for code
    string options[item] = { "New Game", "Continue", "Leaderboard", "Settings", "Exit" };

    // Initialize all text objects for the menu. loop make it easier and above array helps in this
    for (int i = 0; i < item; ++i) 
    {


        //in constructor loop
        menuItems[i].setOutlineThickness(2);
        menuItems[i].setOutlineColor(sf::Color::Black);

        menuItems[i].setFont(font);
        menuItems[i].setString(options[i]);
        menuItems[i].setCharacterSize(26);
        //menuItems[i].setPosition(sf::Vector2f(280, 260 + i*50)); ///vertical space increases
        sf::FloatRect bounds = menuItems[i].getLocalBounds();
        menuItems[i].setOrigin(sf::Vector2f(bounds.size.x / 2, bounds.size.y / 2));

        menuItems[i].setPosition(sf::Vector2f(400, 285 + i * 40));


       
    }

    // the selected option is highlighted
    updateMenuColors();
}

// nothing to clean yet
Menu::~Menu() 
{
   
}

void Menu::draw()
{
    if (!isVisible)
    {
        return;
    }
    window.draw(bgSprite);
    //window.draw(titleText);
    for (int i = 0; i < item; i++) 
    {
        window.draw(optionBoxes[i]);
        window.draw(menuItems[i]);
    }

    selector.setPosition(sf::Vector2f(
        menuItems[choice].getPosition().x - 90,
        menuItems[choice].getPosition().y - 2
    ));
    sf::FloatRect textBounds = menuItems[choice].getLocalBounds();

    selector.setOrigin({
        textBounds.size.x / 2,
        textBounds.size.y / 2
        });

    selector.setPosition({
        menuItems[choice].getPosition().x - 40,
        menuItems[choice].getPosition().y - 5
        });

    window.draw(selector);
}

void Menu::handleInput() 
{
    if (!isVisible)
    {
        return;
    }

    // Use a static clock to hold updating for real-time keyboard input.
    // Without this, pressing S was making the slecting option move very fast
    static sf::Clock Timer;

    // Check if 150 milliseconds have passed since the last input
    if (Timer.getElapsedTime().asMilliseconds() > 150) 
    {

        // this checks keyboard input
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) 
        {
            if (choice - 1 >= 0)
            {
                choice--;

                updateMenuColors();
            }
            else if (choice - 1 < 0)    // wraps around the edges
            {
                choice = item - 1;
                updateMenuColors();
            }
            Timer.restart();
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) 
        {
            if (choice + 1 < item)
            {
                choice++;
                updateMenuColors();
            }
            else if (choice + 1 >= item)
            {
                choice = 0;
                updateMenuColors();
            }            
            Timer.restart();
        }
    }
}

void Menu::updateMenuColors() 
{
    for (int i = 0; i < item; i++) 
    {
        if (i == choice) 
        {
            menuItems[i].setFillColor(sf::Color::Yellow);   // highlight selected option
            optionBoxes[i].setFillColor(sf::Color(50, 50, 150, 220));
        }
        else
        {
            menuItems[i].setFillColor(sf::Color::White); // Default color
            optionBoxes[i].setFillColor(sf::Color(0, 0, 80, 200));
        }

        }
    }


int Menu::getSelectedIndex() const 
{
    return choice;
}