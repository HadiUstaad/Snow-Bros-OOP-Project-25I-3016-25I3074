//#pragma once
//#include <string>
//#include "Display.h"
//#include "Authenticate.h"
//#include <SFML/Graphics.hpp>
//using namespace std;
//
//// Login screen UI for user authentication
//class LoginScreen : public Display
//{
//private:
//    sf::RenderWindow& window;       // reference to game window
//    Authenticate* authManager;       // reference to auth system (not owned)
//
//    sf::Font font;
//    sf::Text titleText;
//    sf::Text usernameLabel;
//    sf::Text passwordLabel;
//    sf::Text usernameField;         // shows typed username
//    sf::Text passwordField;         // shows masked password (*****)
//    sf::Text errorText;
//    sf::Text loginButton;
//    sf::Text registerButton;
//
//    string enteredName;             // typed username
//    string enteredPassword;          // typed password. it is .....
//    int selectedField;              // 0=username 1=password 2=login 3=register
//    bool showError;
//    string errorMessage;
//
//public:
//    LoginScreen(sf::RenderWindow& gameWindow, Authenticate* auth);
//    ~LoginScreen() override;
//
//    void draw() override;
//    void handleInput() override;
//
//    // Returns true if a user is currently logged in
//    bool wasLoginSuccessful() const;
//
//    void submitLogin();
//    void switchToRegister();
//    void appendCharacter(char c);
//    void deleteCharacter();
//    void clearFields();
//    void setError(const string& message);
//};


//#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include"MenuDisplay.h"
#include "Authenticate.h"


//class Display
//{
//protected:
//    bool isVisible;
//public:
//    Display(bool visible) : isVisible(visible) {}
//    void show() { isVisible = true; }
//    void hide() { isVisible = false; }
//    bool getIsVisible() const { return isVisible; }
//};

class LoginScreen : public Display
{
public:
    LoginScreen(sf::RenderWindow& gameWindow, Authenticate* auth);
    ~LoginScreen();

    void draw();
    void handleInput();
    bool wasLoginSuccessful() const;

private:
    sf::RenderWindow& window;
    Authenticate* authManager;
    sf::Font font;

    // ── Background panel ──────────────────────────────────────────
    sf::RectangleShape panelBg;         // dark overlay behind the card
    sf::RectangleShape card;            // white/ice card
    sf::RectangleShape cardHeader;      // coloured header strip

    // ── Decorative snowflakes (simple circles) ────────────────────
    static const int FLAKE_COUNT = 8;
    sf::CircleShape snowflakes[FLAKE_COUNT];

    // ── Title ─────────────────────────────────────────────────────
    sf::Text titleText;
    sf::Text subtitleText;

    // ── Username field ────────────────────────────────────────────
    sf::Text usernameLabel;
    sf::RectangleShape usernameBox;
    sf::RectangleShape usernameBoxHighlight;
    sf::Text usernameField;
    sf::Text usernamePlaceholder;

    // ── Password field ────────────────────────────────────────────
    sf::Text passwordLabel;
    sf::RectangleShape passwordBox;
    sf::RectangleShape passwordBoxHighlight;
    sf::Text passwordField;
    sf::Text passwordPlaceholder;

    // ── Buttons ───────────────────────────────────────────────────
    sf::RectangleShape loginBtnBg;
    sf::RectangleShape loginBtnBorder;
    sf::Text loginBtnText;

    sf::RectangleShape registerBtnBg;
    sf::RectangleShape registerBtnBorder;
    sf::Text registerBtnText;

    // ── Tab indicator dots ────────────────────────────────────────
    sf::CircleShape tabDots[4];         // 0=user 1=pass 2=login 3=register
    sf::Text tabHint;

    // ── Error / success message ───────────────────────────────────
    sf::RectangleShape messageBg;
    sf::Text messageText;
    bool showMessage;
    bool isError;                       // red vs green tint

    // ── State ─────────────────────────────────────────────────────
    int selectedField;                  // 0=user 1=pass 2=loginBtn 3=registerBtn
    std::string enteredName;
    std::string enteredPassword;

    // ── Helpers ───────────────────────────────────────────────────
    void submitLogin();
    void submitRegister();
    void appendCharacter(char c);
    void deleteCharacter();
    void clearFields();
    void setMessage(const std::string& msg, bool error);
    void refreshBoxStyles();            // recolour boxes based on selectedField
};