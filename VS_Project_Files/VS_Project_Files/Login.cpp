#include "Login.h"
#include <iostream>
using namespace std;


// text in sfml3 has no default constructor so it i to be initialized before entering the constructor
LoginScreen::LoginScreen(sf::RenderWindow& gameWindow, Authenticate* auth)
    : Display(true), window(gameWindow),
    titleText(font), usernameLabel(font), passwordLabel(font),
    usernameField(font), passwordField(font),
    errorText(font), loginButton(font), registerButton(font)
{
    if (!font.openFromFile("RussoOne-Regular.ttf"))
    {
        cout << "Error: Can not load font 'RussoOne-Regular.ttf'\n";
    }

    authManager = auth;
    selectedField = 0;
    showError = false;
    enteredName = "";
    enteredPassword = "";
    errorMessage = "";

    // Title
    titleText.setFont(font);
    titleText.setString("LOGIN");
    titleText.setCharacterSize(40);
    titleText.setFillColor(sf::Color::White);
    titleText.setPosition(sf::Vector2f(320, 50));

    // Username label
    usernameLabel.setFont(font);
    usernameLabel.setString("Username:");
    usernameLabel.setCharacterSize(20);
    usernameLabel.setFillColor(sf::Color::White);
    usernameLabel.setPosition(sf::Vector2f(200, 150));

    // Username input display
    usernameField.setFont(font);
    usernameField.setString("");
    usernameField.setCharacterSize(20);
    usernameField.setFillColor(sf::Color::Yellow);
    usernameField.setPosition(sf::Vector2f(200, 180));

    // Password label
    passwordLabel.setFont(font);
    passwordLabel.setString("Password:");
    passwordLabel.setCharacterSize(20);
    passwordLabel.setFillColor(sf::Color::White);
    passwordLabel.setPosition(sf::Vector2f(200, 230));

    // Password input display (masked)
    passwordField.setFont(font);
    passwordField.setString("");
    passwordField.setCharacterSize(20);
    passwordField.setFillColor(sf::Color::Yellow);
    passwordField.setPosition(sf::Vector2f(200, 260));

    // Error text
    errorText.setFont(font);
    errorText.setString("");
    errorText.setCharacterSize(16);
    errorText.setFillColor(sf::Color::Red);
    errorText.setPosition(sf::Vector2f(200, 310));

    // Login button
    loginButton.setFont(font);
    loginButton.setString("Login");
    loginButton.setCharacterSize(24);
    loginButton.setFillColor(sf::Color::Green);
    loginButton.setPosition(sf::Vector2f(250, 360));

    // Register button
    registerButton.setFont(font);
    registerButton.setString("Register");
    registerButton.setCharacterSize(24);
    registerButton.setFillColor(sf::Color::White);
    registerButton.setPosition(sf::Vector2f(400, 360));
}

LoginScreen::~LoginScreen()
{
}

void LoginScreen::draw()
{
    if (!isVisible)
    {
        return;
    }

    window.draw(titleText);
    window.draw(usernameLabel);
    window.draw(usernameField);
    window.draw(passwordLabel);
    window.draw(passwordField);

    if (showError)
    {
        window.draw(errorText);
    }

    window.draw(loginButton);
    window.draw(registerButton);
}

void LoginScreen::handleInput()
{
    if (!isVisible)
    {
        return;
    }

    // timer so that aik saath hi 3 4 charachter na record hojai
    static sf::Clock inputTimer;    // static taakay function se baahir bhi chalta hi rahay
    // timer will restart after every input
    if (inputTimer.getElapsedTime().asMilliseconds() < 300)
    {
        return;
    }

    // move to next field. user name to password by pressing TAB
    //modify if loop around the field is needed
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Tab))
    {
        selectedField = (selectedField + 1) % 4;
        inputTimer.restart();
        return;
    }

    // submit action for currently selected field   ENTER
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter))
    {
        if (selectedField == 2) 
        {
            submitLogin();
        }
        else if (selectedField == 3) 
        {
            switchToRegister();
        }
        inputTimer.restart();
        return;
    }

    // delete last character
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Backspace))
    {
        deleteCharacter();
        inputTimer.restart();
        return;
    }

    // Letter / digit input 
    if (selectedField == 0 || selectedField == 1)
    {
        int letterStart= (int)sf::Keyboard::Key::A;
        int letterEnd = (int)sf::Keyboard::Key::Z;
        for (int i = letterStart;i <= letterEnd; i++)
        {
            if (sf::Keyboard::isKeyPressed((sf::Keyboard::Key)i))
            {
                // a has 97 value. when we add the i-A we will reach the correspondin letter in char
                appendCharacter('a' + (i - (int)sf::Keyboard::Key::A));
                inputTimer.restart();
                return;
            }
        }


        letterStart = (int)sf::Keyboard::Key::Num0;
        letterEnd = (int)sf::Keyboard::Key::Num9;

        for (int i = letterStart;i <= letterEnd; i++)
        {
            if (sf::Keyboard::isKeyPressed((sf::Keyboard::Key)i))
            {
                appendCharacter('0' + (i - (int)sf::Keyboard::Key::Num0));
                inputTimer.restart();
                return;
            }
        }
    }
}

void LoginScreen::submitLogin()
{
    showError = false;

    if (authManager->loginUser(enteredName, enteredPassword) == true)
    {
        hide();
        clearFields();
    }
    else
    {
        setError("Invalid username or password");
    }
}

//modify
void LoginScreen::switchToRegister()
{
    setError("Registration not yet implemented");
}

void LoginScreen::appendCharacter(char c)
{
    if (selectedField == 0)
    {
        if (enteredName.size() < 49)
        {
            enteredName = enteredName+c; // add c at end of string
            usernameField.setString(enteredName);
        }
    }
    else if (selectedField == 1)
    {
        if (enteredPassword.size() < 49)
        {
            enteredName = enteredName + c;
            // password is not shown. we only display *
            string password(enteredPassword.size(), '*');
            passwordField.setString(password);
        }
    }
}

void LoginScreen::deleteCharacter()
{
    // empty is a functioon of string to check if it holds nothing
    if (selectedField == 0 && !enteredName.empty())
    {
        enteredName.pop_back(); // the thing that if we had permission to use in Discrete. we would have loved FAST
        usernameField.setString(enteredName);
    }
    else if (selectedField == 1 && !enteredPassword.empty())
    {
        enteredPassword.pop_back();
        string password(enteredPassword.size(), '*');
        passwordField.setString(password);
    }
}

void LoginScreen::clearFields()
{
    enteredName = "";
    enteredPassword = "";
    usernameField.setString("");
    passwordField.setString("");
}

void LoginScreen::setError(const string& message)
{
    showError = true;
    errorMessage = message;
    errorText.setString(errorMessage);
}

bool LoginScreen::wasLoginSuccessful() const
{
    return authManager->isloggedin();
}