
#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "MenuDisplay.h"
#include "Authenticate.h"

class LoginScreen : public Display
{
public:
    LoginScreen(sf::RenderWindow& gameWindow, Authenticate* auth);
    ~LoginScreen();

    void draw();
    void handleInput();
    bool wasLoginSuccessful() const;
    void reset();               // ← NEW: clears fields and resets to initial state

private:
    sf::RenderWindow& window;
    Authenticate* authManager;
    sf::Font font;

    // ── Background panel ──────────────────────────────────────────
    sf::RectangleShape panelBg;
    sf::RectangleShape card;
    sf::RectangleShape cardHeader;

    // ── Decorative snowflakes ─────────────────────────────────────
    static const int FLAKE_COUNT = 8;
    sf::CircleShape snowflakes[FLAKE_COUNT];

    // ── Title ─────────────────────────────────────────────────────
    sf::Text titleText;
    sf::Text subtitleText;

    // ── Username field ────────────────────────────────────────────
    sf::Text              usernameLabel;
    sf::RectangleShape    usernameBox;
    sf::RectangleShape    usernameBoxHighlight;
    sf::Text              usernameField;
    sf::Text              usernamePlaceholder;

    // ── Password field ────────────────────────────────────────────
    sf::Text              passwordLabel;
    sf::RectangleShape    passwordBox;
    sf::RectangleShape    passwordBoxHighlight;
    sf::Text              passwordField;
    sf::Text              passwordPlaceholder;

    // ── Buttons ───────────────────────────────────────────────────
    sf::RectangleShape loginBtnBg;
    sf::RectangleShape loginBtnBorder;
    sf::Text           loginBtnText;

    sf::RectangleShape registerBtnBg;
    sf::RectangleShape registerBtnBorder;
    sf::Text           registerBtnText;

    // ── Tab indicator dots ────────────────────────────────────────
    sf::CircleShape tabDots[4];
    sf::Text        tabHint;

    // ── Error / success message ───────────────────────────────────
    sf::RectangleShape messageBg;
    sf::Text           messageText;
    bool               showMessage;
    bool               isError;

    // ── State ─────────────────────────────────────────────────────
    int         selectedField;
    std::string enteredName;
    std::string enteredPassword;

    // ── Helpers ───────────────────────────────────────────────────
    void submitLogin();
    void submitRegister();
    void appendCharacter(char c);
    void deleteCharacter();
    void clearFields();
    void setMessage(const std::string& msg, bool error);
    void refreshBoxStyles();
};