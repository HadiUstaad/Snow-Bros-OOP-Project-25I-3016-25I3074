#include "Login.h"
#include <iostream>
using namespace std;


static const sf::Color COL_DARK_BG(10, 20, 45, 230); // deep navy overlay
static const sf::Color COL_CARD_BG(230, 245, 255, 255); // ice-white card
static const sf::Color COL_HEADER_BG(30, 90, 200, 255); // royal blue header
static const sf::Color COL_HEADER_DARK(20, 60, 150, 255); // darker blue accent
static const sf::Color COL_TITLE(255, 255, 255, 255); // white title text
static const sf::Color COL_LABEL(40, 60, 100, 255); // dark-blue labels
static const sf::Color COL_INPUT_TEXT(10, 30, 80, 255); // text inside boxes
static const sf::Color COL_PLACEHOLDER(160, 185, 215, 255); // placeholder hint
static const sf::Color COL_BOX_NORMAL(185, 215, 240, 255); // input box border idle
static const sf::Color COL_BOX_ACTIVE(30, 120, 255, 255); // input box border focused
static const sf::Color COL_BOX_FILL(245, 252, 255, 255); // input box background
static const sf::Color COL_BTN_LOGIN(30, 130, 230, 255); // login button
static const sf::Color COL_BTN_LOGIN_H(20, 100, 190, 255); // login button hover
static const sf::Color COL_BTN_REG(245, 248, 255, 255); // register button (outline)
static const sf::Color COL_BTN_REG_BD(30, 90, 200, 255); // register button border
static const sf::Color COL_BTN_ACTIVE(255, 230, 80, 255); // yellow glow when selected
static const sf::Color COL_ERR_BG(255, 230, 230, 255);
static const sf::Color COL_ERR_TEXT(180, 30, 30, 255);
static const sf::Color COL_OK_BG(220, 255, 230, 255);
static const sf::Color COL_OK_TEXT(20, 140, 50, 255);
static const sf::Color COL_SNOW(200, 230, 255, 120); // decorative snowflakes
static const sf::Color COL_DOT_IDLE(160, 190, 220, 255);
static const sf::Color COL_DOT_ACTIVE(30, 120, 255, 255);


static const float WIN_W = 800.f;
static const float WIN_H = 600.f;
static const float CARD_W = 400.f;
static const float CARD_H = 420.f;
static const float CARD_X = (WIN_W - CARD_W) / 2.f;   // 200
static const float CARD_Y = (WIN_H - CARD_H) / 2.f;   // 90
static const float HDR_H = 90.f;
static const float PAD = 28.f;
static const float BOX_H = 42.f;
static const float BOX_W = CARD_W - PAD * 2.f;       // 344
static const float BTN_H = 44.f;
static const float BTN_W = (BOX_W - 16.f) / 2.f;    // 164

// row Y positions with respect to card
static const float ROW_USER_LBL = HDR_H + 22.f;
static const float ROW_USER_BOX = ROW_USER_LBL + 22.f;
static const float ROW_PASS_LBL = ROW_USER_BOX + BOX_H + 14.f;
static const float ROW_PASS_BOX = ROW_PASS_LBL + 22.f;
static const float ROW_BTN = ROW_PASS_BOX + BOX_H + 22.f;
static const float ROW_MSG = ROW_BTN + BTN_H + 12.f;
static const float ROW_HINT = CARD_H - 26.f;


LoginScreen::LoginScreen(sf::RenderWindow& gameWindow, Authenticate* auth)
    : Display(true), window(gameWindow),
    titleText(font), subtitleText(font),
    usernameLabel(font), usernameField(font), usernamePlaceholder(font),
    passwordLabel(font), passwordField(font), passwordPlaceholder(font),
    loginBtnText(font), registerBtnText(font),
    tabHint(font), messageText(font)
{
    if (!font.openFromFile("RussoOne-Regular.ttf"))
        cout << "Login: font load failed\n";

    authManager = auth;
    selectedField = 0;
    showMessage = false;
    isError = false;
    enteredName = "";
    enteredPassword = "";

   
    panelBg.setSize({ WIN_W, WIN_H });
    panelBg.setFillColor(COL_DARK_BG);
    panelBg.setPosition({ 0, 0 });

    
    card.setSize({ CARD_W, CARD_H });
    card.setFillColor(COL_CARD_BG);
    card.setOutlineThickness(2.f);
    card.setOutlineColor(COL_BOX_NORMAL);
    card.setPosition({ CARD_X, CARD_Y });

    
    cardHeader.setSize({ CARD_W, HDR_H });
    cardHeader.setFillColor(COL_HEADER_BG);
    cardHeader.setPosition({ CARD_X, CARD_Y });

    
    float fx[] = { 50, 140, 600, 700, 30,  730, 370, 420 };
    float fy[] = { 80, 480, 60,  400, 300, 200, 30,  550 };
    float fr[] = { 18, 12,  20,  14,  10,  16,  8,   22 };
    for (int i = 0; i < FLAKE_COUNT; i++)
    {
        snowflakes[i].setRadius(fr[i]);
        snowflakes[i].setOrigin({ fr[i], fr[i] });
        snowflakes[i].setPosition({ fx[i], fy[i] });
        snowflakes[i].setFillColor(COL_SNOW);
        snowflakes[i].setOutlineColor(sf::Color(150, 200, 255, 80));
        snowflakes[i].setOutlineThickness(2.f);
    }

   
    titleText.setFont(font);
    titleText.setString("SNOW BROS");
    titleText.setCharacterSize(28);
    titleText.setFillColor(COL_TITLE);
    titleText.setPosition({ CARD_X + PAD, CARD_Y + 12.f });

    subtitleText.setFont(font);
    subtitleText.setString("Sign in to continue");
    subtitleText.setCharacterSize(13);
    subtitleText.setFillColor(sf::Color(180, 210, 255, 200));
    subtitleText.setPosition({ CARD_X + PAD, CARD_Y + 48.f });

    
    
    usernameLabel.setFont(font);
    usernameLabel.setString("USERNAME");
    usernameLabel.setCharacterSize(11);
    usernameLabel.setFillColor(COL_LABEL);
    usernameLabel.setLetterSpacing(2.f);
    usernameLabel.setPosition({ CARD_X + PAD, CARD_Y + ROW_USER_LBL });

    usernameBox.setSize({ BOX_W, BOX_H });
    usernameBox.setFillColor(COL_BOX_FILL);
    usernameBox.setOutlineThickness(2.f);
    usernameBox.setOutlineColor(COL_BOX_ACTIVE);   // starts focused
    usernameBox.setPosition({ CARD_X + PAD, CARD_Y + ROW_USER_BOX });

    usernameField.setFont(font);
    usernameField.setString("");
    usernameField.setCharacterSize(17);
    usernameField.setFillColor(COL_INPUT_TEXT);
    usernameField.setPosition({ CARD_X + PAD + 12.f, CARD_Y + ROW_USER_BOX + 10.f });

    usernamePlaceholder.setFont(font);
    usernamePlaceholder.setString("Enter your username...");
    usernamePlaceholder.setCharacterSize(15);
    usernamePlaceholder.setFillColor(COL_PLACEHOLDER);
    usernamePlaceholder.setPosition({ CARD_X + PAD + 12.f, CARD_Y + ROW_USER_BOX + 12.f });

    
    passwordLabel.setFont(font);
    passwordLabel.setString("PASSWORD");
    passwordLabel.setCharacterSize(11);
    passwordLabel.setFillColor(COL_LABEL);
    passwordLabel.setLetterSpacing(2.f);
    passwordLabel.setPosition({ CARD_X + PAD, CARD_Y + ROW_PASS_LBL });

    passwordBox.setSize({ BOX_W, BOX_H });
    passwordBox.setFillColor(COL_BOX_FILL);
    passwordBox.setOutlineThickness(2.f);
    passwordBox.setOutlineColor(COL_BOX_NORMAL);
    passwordBox.setPosition({ CARD_X + PAD, CARD_Y + ROW_PASS_BOX });

    passwordField.setFont(font);
    passwordField.setString("");
    passwordField.setCharacterSize(17);
    passwordField.setFillColor(COL_INPUT_TEXT);
    passwordField.setPosition({ CARD_X + PAD + 12.f, CARD_Y + ROW_PASS_BOX + 10.f });

    passwordPlaceholder.setFont(font);
    passwordPlaceholder.setString("Enter your password...");
    passwordPlaceholder.setCharacterSize(15);
    passwordPlaceholder.setFillColor(COL_PLACEHOLDER);
    passwordPlaceholder.setPosition({ CARD_X + PAD + 12.f, CARD_Y + ROW_PASS_BOX + 12.f });

   
    loginBtnBg.setSize({ BTN_W, BTN_H });
    loginBtnBg.setFillColor(COL_BTN_LOGIN);
    loginBtnBg.setOutlineThickness(3.f);
    loginBtnBg.setOutlineColor(sf::Color::Transparent);
    loginBtnBg.setPosition({ CARD_X + PAD, CARD_Y + ROW_BTN });

    loginBtnText.setFont(font);
    loginBtnText.setString("LOGIN");
    loginBtnText.setCharacterSize(15);
    loginBtnText.setFillColor(sf::Color::White);
    // centre text in button â€” approximate
    loginBtnText.setPosition({ CARD_X + PAD + BTN_W / 2.f - 32.f,
                               CARD_Y + ROW_BTN + 12.f });

    
    float regBtnX = CARD_X + PAD + BTN_W + 16.f;
    registerBtnBg.setSize({ BTN_W, BTN_H });
    registerBtnBg.setFillColor(COL_BTN_REG);
    registerBtnBg.setOutlineThickness(2.f);
    registerBtnBg.setOutlineColor(COL_BTN_REG_BD);
    registerBtnBg.setPosition({ regBtnX, CARD_Y + ROW_BTN });

    registerBtnText.setFont(font);
    registerBtnText.setString("REGISTER");
    registerBtnText.setCharacterSize(15);
    registerBtnText.setFillColor(COL_BTN_REG_BD);
    registerBtnText.setPosition({ regBtnX + BTN_W / 2.f - 46.f,
                                  CARD_Y + ROW_BTN + 12.f });

  
    messageBg.setSize({ BOX_W, 32.f });
    messageBg.setFillColor(COL_ERR_BG);
    messageBg.setPosition({ CARD_X + PAD, CARD_Y + ROW_MSG });

    messageText.setFont(font);
    messageText.setString("");
    messageText.setCharacterSize(12);
    messageText.setFillColor(COL_ERR_TEXT);
    messageText.setPosition({ CARD_X + PAD + 8.f, CARD_Y + ROW_MSG + 8.f });

    
    float dotY = CARD_Y + ROW_HINT + 4.f;
    float dotStartX = CARD_X + CARD_W / 2.f - 30.f;
    for (int i = 0; i < 4; i++)
    {
        tabDots[i].setRadius(5.f);
        tabDots[i].setOrigin({ 5.f, 5.f });
        tabDots[i].setPosition({ dotStartX + i * 20.f, dotY });
        tabDots[i].setFillColor(COL_DOT_IDLE);
    }

    tabHint.setFont(font);
    tabHint.setString("TAB to switch   ENTER to confirm");
    tabHint.setCharacterSize(10);
    tabHint.setFillColor(COL_LABEL);
    tabHint.setPosition({ CARD_X + PAD, CARD_Y + ROW_HINT });

    refreshBoxStyles();
}

LoginScreen::~LoginScreen() {}


void LoginScreen::refreshBoxStyles()
{
    // input boxes
    usernameBox.setOutlineColor(selectedField == 0 ? COL_BOX_ACTIVE : COL_BOX_NORMAL);
    passwordBox.setOutlineColor(selectedField == 1 ? COL_BOX_ACTIVE : COL_BOX_NORMAL);

    // button glow
    loginBtnBg.setOutlineColor(selectedField == 2 ? COL_BTN_ACTIVE : sf::Color::Transparent);
    loginBtnBg.setFillColor(selectedField == 2 ? COL_BTN_LOGIN_H : COL_BTN_LOGIN);

    registerBtnBg.setOutlineColor(selectedField == 3 ? COL_BTN_ACTIVE : COL_BTN_REG_BD);
    registerBtnBg.setFillColor(selectedField == 3 ? sf::Color(220, 235, 255, 255) : COL_BTN_REG);

    // tab dots
    for (int i = 0; i < 4; i++)
        tabDots[i].setFillColor(i == selectedField ? COL_DOT_ACTIVE : COL_DOT_IDLE);
}


void LoginScreen::draw()
{
    if (!isVisible) return;

    // background overlay
    window.draw(panelBg);

    // decorative snowflakes
    for (int i = 0; i < FLAKE_COUNT; i++)
        window.draw(snowflakes[i]);

    // card body
    window.draw(card);
    window.draw(cardHeader);

    // title
    window.draw(titleText);
    window.draw(subtitleText);

    // username
    window.draw(usernameLabel);
    window.draw(usernameBox);
    if (enteredName.empty())
        window.draw(usernamePlaceholder);
    window.draw(usernameField);

    // password
    window.draw(passwordLabel);
    window.draw(passwordBox);
    if (enteredPassword.empty())
        window.draw(passwordPlaceholder);
    window.draw(passwordField);

    // buttons
    window.draw(loginBtnBg);
    window.draw(loginBtnText);
    window.draw(registerBtnBg);
    window.draw(registerBtnText);

    // message
    if (showMessage)
    {
        window.draw(messageBg);
        window.draw(messageText);
    }

    // nav hint + dots
    window.draw(tabHint);
    for (int i = 0; i < 4; i++)
        window.draw(tabDots[i]);
}


void LoginScreen::handleInput()
{
    if (!isVisible) return;

    static sf::Clock inputTimer;
    if (inputTimer.getElapsedTime().asMilliseconds() < 150)
        return;

    // TAB â†’ cycle fields
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Tab))
    {
        selectedField = (selectedField + 1) % 4;
        showMessage = false;
        refreshBoxStyles();
        inputTimer.restart();
        return;
    }

    // ENTER â†’ action on current selection
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter))
    {
        if (selectedField == 0) { selectedField = 1; refreshBoxStyles(); }
        else if (selectedField == 1) { selectedField = 2; refreshBoxStyles(); }
        else if (selectedField == 2) { submitLogin(); }
        else if (selectedField == 3) { submitRegister(); }
        inputTimer.restart();
        return;
    }

    // BACKSPACE
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Backspace))
    {
        deleteCharacter();
        inputTimer.restart();
        return;
    }

    // Letters A-Z  (only when on a text field)
    if (selectedField == 0 || selectedField == 1)
    {
        int a = (int)sf::Keyboard::Key::A;
        int z = (int)sf::Keyboard::Key::Z;
        for (int i = a; i <= z; i++)
        {
            if (sf::Keyboard::isKeyPressed((sf::Keyboard::Key)i))
            {
                appendCharacter((char)('a' + (i - a)));
                inputTimer.restart();
                return;
            }
        }

        // Digits 0-9
        int n0 = (int)sf::Keyboard::Key::Num0;
        int n9 = (int)sf::Keyboard::Key::Num9;
        for (int i = n0; i <= n9; i++)
        {
            if (sf::Keyboard::isKeyPressed((sf::Keyboard::Key)i))
            {
                appendCharacter((char)('0' + (i - n0)));
                inputTimer.restart();
                return;
            }
        }
    }
}


void LoginScreen::submitLogin()
{
    if (enteredName.empty() || enteredPassword.empty())
    {
        setMessage("Please fill in both fields", true);
        return;
    }

    if (authManager->loginUser(enteredName, enteredPassword))
    {
        setMessage("Welcome back, " + enteredName + "!", false);
        hide();
        clearFields();
    }
    else
    {
        setMessage("Wrong username or password", true);
    }
}


void LoginScreen::submitRegister()
{
    if (enteredName.empty() || enteredPassword.empty())
    {
        setMessage("Please fill in both fields", true);
        return;
    }

    if (authManager->registerUser(enteredName, enteredPassword))
    {
        setMessage("Account created! Now login.", false);
        selectedField = 2;   // move focus to login button
        refreshBoxStyles();
    }
    else
    {
        // Give a more specific hint
        if (enteredName.size() < 3)
            setMessage("Username must be 3-20 chars", true);
        else if (enteredPassword.size() < 6)
            setMessage("Password must be 6-8 chars", true);
        else
            setMessage("Username already taken", true);
    }
}


void LoginScreen::appendCharacter(char c)
{
    showMessage = false;

    if (selectedField == 0)
    {
        if (enteredName.size() < 20)
        {
            enteredName += c;
            usernameField.setString(enteredName);
        }
    }
    else if (selectedField == 1)
    {
        if (enteredPassword.size() < 8)
        {
            enteredPassword += c;
            string masked(enteredPassword.size(), '*');
            passwordField.setString(masked);
        }
    }
}


void LoginScreen::deleteCharacter()
{
    showMessage = false;

    if (selectedField == 0 && !enteredName.empty())
    {
        enteredName.pop_back();
        usernameField.setString(enteredName);
    }
    else if (selectedField == 1 && !enteredPassword.empty())
    {
        enteredPassword.pop_back();
        string masked(enteredPassword.size(), '*');
        passwordField.setString(masked);
    }
}



void LoginScreen::clearFields()
{
    enteredName = "";
    enteredPassword = "";
    usernameField.setString("");
    passwordField.setString("");
}


void LoginScreen::setMessage(const string& msg, bool error)
{
    showMessage = true;
    isError = error;
    messageText.setString(msg);
    messageText.setFillColor(error ? COL_ERR_TEXT : COL_OK_TEXT);
    messageBg.setFillColor(error ? COL_ERR_BG : COL_OK_BG);
}


bool LoginScreen::wasLoginSuccessful() const
{
    return authManager->isloggedin();
}

void LoginScreen::reset()
{
    clearFields();              // wipes enteredName, enteredPassword, and sf::Text strings

    selectedField = 0;          // focus back to username box
    showMessage = false;      // hide any error/success banner
    isError = false;

    authManager->logout();      // make sure the auth state is cleared too

    show();                     // make the screen visible again
    refreshBoxStyles();         // reset box highlights to initial state (username focused)
}