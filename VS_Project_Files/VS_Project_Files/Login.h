#pragma once
#include <string>
#include "Display.h"
#include "Authenticate.h"
#include <SFML/Graphics.hpp>
using namespace std;

// Login screen UI for user authentication
class LoginScreen : public Display
{
private:
    sf::RenderWindow& window;       // reference to game window
    Authenticate* authManager;       // reference to auth system (not owned)

    sf::Font font;
    sf::Text titleText;
    sf::Text usernameLabel;
    sf::Text passwordLabel;
    sf::Text usernameField;         // shows typed username
    sf::Text passwordField;         // shows masked password (*****)
    sf::Text errorText;
    sf::Text loginButton;
    sf::Text registerButton;

    string enteredName;             // typed username
    string enteredPassword;          // typed password. it is .....
    int selectedField;              // 0=username 1=password 2=login 3=register
    bool showError;
    string errorMessage;

public:
    LoginScreen(sf::RenderWindow& gameWindow, Authenticate* auth);
    ~LoginScreen() override;

    void draw() override;
    void handleInput() override;

    // Returns true if a user is currently logged in
    bool wasLoginSuccessful() const;

    void submitLogin();
    void switchToRegister();
    void appendCharacter(char c);
    void deleteCharacter();
    void clearFields();
    void setError(const string& message);
};