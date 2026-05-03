#include "Shop.h"
#include <iostream>
using namespace std;

// =============================================================================
// PowerUpState
// =============================================================================

PowerUpState::PowerUpState()
    : speedBoost(false), doubleScore(false), widerShot(false),
    extraLifeOwned(0), speedBoostOwned(0),
    doubleScoreOwned(0), widerShotOwned(0)
{
}

void PowerUpState::setSpeedBoost(bool val) { speedBoost = val; }
void PowerUpState::setDoubleScore(bool val) { doubleScore = val; }
void PowerUpState::setWiderShot(bool val) { widerShot = val; }

void PowerUpState::incrementExtraLife() { extraLifeOwned++; }
void PowerUpState::incrementSpeedBoost() { speedBoostOwned++; }
void PowerUpState::incrementDoubleScore() { doubleScoreOwned++; }
void PowerUpState::incrementWiderShot() { widerShotOwned++; }

bool PowerUpState::getSpeedBoost()  const { return speedBoost; }
bool PowerUpState::getDoubleScore() const { return doubleScore; }
bool PowerUpState::getWiderShot()   const { return widerShot; }

int PowerUpState::getExtraLifeOwned()   const { return extraLifeOwned; }
int PowerUpState::getSpeedBoostOwned()  const { return speedBoostOwned; }
int PowerUpState::getDoubleScoreOwned() const { return doubleScoreOwned; }
int PowerUpState::getWiderShotOwned()   const { return widerShotOwned; }

void PowerUpState::reset() { *this = PowerUpState(); }


// =============================================================================
// ShopItem
// =============================================================================

ShopItem::ShopItem()
    : name(""), description(""), flavorText(""), cost(0), maxOwned(0)
{
}

ShopItem::ShopItem(const string& n, const string& desc,
    const string& flavor, int c, int m)
    : name(n), description(desc), flavorText(flavor), cost(c), maxOwned(m)
{
}

string ShopItem::getName()        const { return name; }
string ShopItem::getDescription() const { return description; }
string ShopItem::getFlavorText()  const { return flavorText; }
int    ShopItem::getCost()        const { return cost; }
int    ShopItem::getMaxOwned()    const { return maxOwned; }


// =============================================================================
// ShopScreen — Constructor
//
// SFML 3 requires sf::Text(font) — no default constructor exists.
// Steps taken here:
//   1. Load font FIRST (font is a plain member, not a pointer).
//   2. Pass font to every non-array sf::Text in the member-initialiser list.
//   3. Allocate per-item sf::Text* pointers in the constructor BODY after
//      the font is confirmed loaded.
// =============================================================================

ShopScreen::ShopScreen(sf::RenderWindow& gameWindow,
    Currency* p1Gems, Currency* p2Gems,
    PowerUpState* state)
    : Display(true),
    window(gameWindow),
    powerUps(state),
    // font is default-constructed (sf::Font has a default ctor — fine)
    // Now pass font to every fixed sf::Text member:
    titleText(font),
    gemText(font),
    playerTag(font),
    backHint(font),
    feedbackText(font),
    showFeedback(false),
    selected(0),
    activePlayer(0),
    purchaseFlag(false),
    lastBought(-1)
{
    // ── Assign currency pointers ──────────────────────────────────────────
    gems[0] = p1Gems;
    gems[1] = p2Gems;

    // ── Null-initialise pointer arrays before anything can throw ─────────
    for (int i = 0; i < ITEM_COUNT; i++)
    {
        itemName[i] = nullptr;
        itemDesc[i] = nullptr;
        itemFlavor[i] = nullptr;
        itemCost[i] = nullptr;
        itemOwned[i] = nullptr;
        buyBtnText[i] = nullptr;
    }

    // ── Load font ─────────────────────────────────────────────────────────
    if (!font.openFromFile("RussoOne-Regular.ttf"))
    {
        cout << "[ShopScreen] WARNING: Could not load RussoOne-Regular.ttf\n";
    }

    // Re-apply font to header texts after the font object is populated.
    // (The initialiser list captured a reference to font before it was loaded,
    //  so we set it explicitly here to be safe with SFML 3.)
    titleText.setFont(font);
    gemText.setFont(font);
    playerTag.setFont(font);
    backHint.setFont(font);
    feedbackText.setFont(font);

    // ── Allocate per-item sf::Text objects NOW that font is loaded ────────
    for (int i = 0; i < ITEM_COUNT; i++)
    {
        itemName[i] = new sf::Text(font);
        itemDesc[i] = new sf::Text(font);
        itemFlavor[i] = new sf::Text(font);
        itemCost[i] = new sf::Text(font);
        itemOwned[i] = new sf::Text(font);
        buyBtnText[i] = new sf::Text(font);
    }

    // ── Define shop items ─────────────────────────────────────────────────
    items[0] = ShopItem("Extra Life", "+1 Life", "Stay in the fight!", 50, 5);
    items[1] = ShopItem("Speed Boost", "Move faster", "Leave them in dust", 40, 0);
    items[2] = ShopItem("Double Score", "2x points", "Score like a legend", 60, 0);
    items[3] = ShopItem("Wide Shot", "Bigger attack", "Hit more, miss less", 45, 0);

    // ── Background overlay ────────────────────────────────────────────────
    overlay.setSize(sf::Vector2f(800.f, 600.f));
    overlay.setFillColor(sf::Color(0, 0, 0, 180));
    overlay.setPosition({ 0.f, 0.f });

    // ── Panel ─────────────────────────────────────────────────────────────
    panel.setSize(sf::Vector2f(620.f, 520.f));
    panel.setFillColor(sf::Color(20, 20, 35));
    panel.setOutlineColor(sf::Color(80, 120, 200));
    panel.setOutlineThickness(2.f);
    panel.setPosition({ 90.f, 40.f });

    // ── Header bar ────────────────────────────────────────────────────────
    headerBar.setSize(sf::Vector2f(620.f, 60.f));
    headerBar.setFillColor(sf::Color(35, 35, 60));
    headerBar.setPosition({ 90.f, 40.f });

    accentLine.setSize(sf::Vector2f(620.f, 3.f));
    accentLine.setFillColor(sf::Color(100, 160, 255));
    accentLine.setPosition({ 90.f, 100.f });

    footerLine.setSize(sf::Vector2f(620.f, 2.f));
    footerLine.setFillColor(sf::Color(60, 60, 100));
    footerLine.setPosition({ 90.f, 530.f });

    // ── Title text ────────────────────────────────────────────────────────
    titleText.setCharacterSize(32);
    titleText.setFillColor(sf::Color(200, 220, 255));
    titleText.setStyle(sf::Text::Bold);
    titleText.setString("SHOP");
    titleText.setPosition({ 360.f, 52.f });

    // ── Gem display ───────────────────────────────────────────────────────
    gemText.setCharacterSize(18);
    gemText.setFillColor(sf::Color(255, 215, 0));
    gemText.setPosition({ 100.f, 58.f });

    // ── Player tag ────────────────────────────────────────────────────────
    playerTag.setCharacterSize(16);
    playerTag.setFillColor(sf::Color(150, 200, 255));
    playerTag.setPosition({ 560.f, 60.f });

    // ── Back hint ─────────────────────────────────────────────────────────
    backHint.setCharacterSize(15);
    backHint.setFillColor(sf::Color(120, 120, 140));
    backHint.setString("ESC - Back    ENTER - Buy    UP/DOWN - Navigate");
    backHint.setPosition({ 130.f, 540.f });

    // ── Feedback text ─────────────────────────────────────────────────────
    feedbackText.setCharacterSize(18);
    feedbackText.setPosition({ 300.f, 510.f });

    // ── Per-item card layout ──────────────────────────────────────────────
    const float CARD_X = 110.f;
    const float CARD_Y_START = 115.f;
    const float CARD_H = 90.f;
    const float CARD_GAP = 8.f;
    const float CARD_W = 580.f;

    for (int i = 0; i < ITEM_COUNT; i++)
    {
        float cy = CARD_Y_START + i * (CARD_H + CARD_GAP);

        // Card background
        cardBg[i].setSize(sf::Vector2f(CARD_W, CARD_H));
        cardBg[i].setFillColor(sf::Color(30, 30, 50));
        cardBg[i].setPosition({ CARD_X, cy });

        // Coloured left accent strip
        cardBorder[i].setSize(sf::Vector2f(5.f, CARD_H));
        cardBorder[i].setFillColor(itemAccentColor(i));
        cardBorder[i].setPosition({ CARD_X, cy });

        // Selection highlight outline (hidden by default)
        cardHighlight[i].setSize(sf::Vector2f(CARD_W, CARD_H));
        cardHighlight[i].setFillColor(sf::Color::Transparent);
        cardHighlight[i].setOutlineThickness(2.f);
        cardHighlight[i].setOutlineColor(sf::Color::Transparent);
        cardHighlight[i].setPosition({ CARD_X, cy });

        // Icon circle
        itemIcon[i].setRadius(22.f);
        itemIcon[i].setFillColor(itemAccentColor(i));
        itemIcon[i].setPosition({ CARD_X + 14.f, cy + CARD_H / 2.f - 22.f });

        // Item name
        itemName[i]->setCharacterSize(20);
        itemName[i]->setFillColor(sf::Color::White);
        itemName[i]->setStyle(sf::Text::Bold);
        itemName[i]->setString(items[i].getName());
        itemName[i]->setPosition({ CARD_X + 70.f, cy + 10.f });

        // Item description
        itemDesc[i]->setCharacterSize(15);
        itemDesc[i]->setFillColor(sf::Color(180, 180, 200));
        itemDesc[i]->setString(items[i].getDescription());
        itemDesc[i]->setPosition({ CARD_X + 70.f, cy + 36.f });

        // Flavor text
        itemFlavor[i]->setCharacterSize(13);
        itemFlavor[i]->setFillColor(sf::Color(120, 120, 140));
        itemFlavor[i]->setStyle(sf::Text::Italic);
        itemFlavor[i]->setString(items[i].getFlavorText());
        itemFlavor[i]->setPosition({ CARD_X + 70.f, cy + 57.f });

        // Buy button background
        buyBtnBg[i].setSize(sf::Vector2f(90.f, 36.f));
        buyBtnBg[i].setFillColor(sf::Color(50, 80, 160));
        buyBtnBg[i].setPosition({ CARD_X + CARD_W - 200.f, cy + CARD_H / 2.f - 18.f });

        // Buy button text
        buyBtnText[i]->setCharacterSize(15);
        buyBtnText[i]->setFillColor(sf::Color::White);
        buyBtnText[i]->setString("BUY");
        buyBtnText[i]->setPosition({ CARD_X + CARD_W - 186.f, cy + CARD_H / 2.f - 11.f });

        // Cost text
        itemCost[i]->setCharacterSize(18);
        itemCost[i]->setFillColor(sf::Color(255, 215, 0));
        itemCost[i]->setString(to_string(items[i].getCost()) + " G");
        itemCost[i]->setPosition({ CARD_X + CARD_W - 100.f, cy + CARD_H / 2.f - 12.f });

        // Owned count
        itemOwned[i]->setCharacterSize(13);
        itemOwned[i]->setFillColor(sf::Color(140, 200, 140));
        itemOwned[i]->setPosition({ CARD_X + CARD_W - 200.f, cy + 5.f });
    }
}


// =============================================================================
// ShopScreen — Destructor
// Delete every sf::Text pointer to avoid memory leaks.
// =============================================================================

ShopScreen::~ShopScreen()
{
    for (int i = 0; i < ITEM_COUNT; i++)
    {
        delete itemName[i];
        delete itemDesc[i];
        delete itemFlavor[i];
        delete itemCost[i];
        delete itemOwned[i];
        delete buyBtnText[i];

        itemName[i] = nullptr;
        itemDesc[i] = nullptr;
        itemFlavor[i] = nullptr;
        itemCost[i] = nullptr;
        itemOwned[i] = nullptr;
        buyBtnText[i] = nullptr;
    }
}


// =============================================================================
// draw()
// =============================================================================

void ShopScreen::draw()
{
    // Dim background
    window.draw(overlay);

    // Panel
    window.draw(panel);
    window.draw(headerBar);
    window.draw(accentLine);
    window.draw(footerLine);

    // Header
    titleText.setString("SHOP");
    window.draw(titleText);

    // Gem counter
    if (gems[activePlayer] != nullptr)
        gemText.setString("Gems: " + to_string(gems[activePlayer]->getGems()));
    window.draw(gemText);

    // Player tag
    playerTag.setString(activePlayer == 0 ? "P1" : "P2");
    window.draw(playerTag);

    window.draw(backHint);

    // Update selection highlight
    updateCardStyles();

    // Cards
    for (int i = 0; i < ITEM_COUNT; i++)
    {
        window.draw(cardBg[i]);
        window.draw(cardBorder[i]);
        window.draw(cardHighlight[i]);
        window.draw(itemIcon[i]);

        // Update owned count string each frame
        int owned = getOwnedCount(i);
        int maxO = items[i].getMaxOwned();
        if (maxO > 0)
            itemOwned[i]->setString("Owned: " + to_string(owned) + "/" + to_string(maxO));
        else
            itemOwned[i]->setString("Owned: " + to_string(owned));

        window.draw(*itemName[i]);
        window.draw(*itemDesc[i]);
        window.draw(*itemFlavor[i]);
        window.draw(buyBtnBg[i]);
        window.draw(*buyBtnText[i]);
        window.draw(*itemCost[i]);
        window.draw(*itemOwned[i]);
    }

    // Feedback message
    if (showFeedback)
    {
        if (feedbackTimer.getElapsedTime().asSeconds() < 1.5f)
            window.draw(feedbackText);
        else
            showFeedback = false;
    }
}


// =============================================================================
// handleInput()
// =============================================================================

void ShopScreen::handleInput()
{
    static sf::Clock inputClock;
    if (inputClock.getElapsedTime().asMilliseconds() < 180)
        return;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
    {
        selected = (selected == 0) ? ITEM_COUNT - 1 : selected - 1;
        inputClock.restart();
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
    {
        selected = (selected + 1) % ITEM_COUNT;
        inputClock.restart();
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter))
    {
        tryBuy(selected);
        inputClock.restart();
    }
}


// =============================================================================
// tryBuy()
// =============================================================================

void ShopScreen::tryBuy(int index)
{
    if (gems[activePlayer] == nullptr) return;

    int cost = items[index].getCost();
    int maxO = items[index].getMaxOwned();
    int owned = getOwnedCount(index);

    // Check max ownership cap (0 = unlimited)
    if (maxO > 0 && owned >= maxO)
    {
        feedbackText.setFillColor(sf::Color(255, 100, 100));
        feedbackText.setString("Max owned!");
        showFeedback = true;
        feedbackTimer.restart();
        return;
    }

    if (gems[activePlayer]->getGems() < cost)
    {
        feedbackText.setFillColor(sf::Color(255, 100, 100));
        feedbackText.setString("Not enough gems!");
        showFeedback = true;
        feedbackTimer.restart();
        return;
    }

    // Deduct gems and apply
    gems[activePlayer]->addGems(-cost);

    purchaseFlag = true;
    lastBought = index;

    activateFlag(index);
    incrementOwned(index);

    feedbackText.setFillColor(sf::Color(100, 255, 150));
    feedbackText.setString("Purchased: " + items[index].getName() + "!");
    showFeedback = true;
    feedbackTimer.restart();
}


// =============================================================================
// Public accessors
// =============================================================================

bool ShopScreen::wasPurchased() { return purchaseFlag; }
int  ShopScreen::lastPurchasedIndex() { return lastBought; }
void ShopScreen::resetPurchaseFlag() { purchaseFlag = false; }

void ShopScreen::setActivePlayer(int p)
{
    activePlayer = (p == 0 || p == 1) ? p : 0;
}


// =============================================================================
// Private helpers
// =============================================================================

void ShopScreen::updateCardStyles()
{
    for (int i = 0; i < ITEM_COUNT; i++)
    {
        if (i == selected)
        {
            cardBg[i].setFillColor(sf::Color(45, 45, 75));
            cardHighlight[i].setOutlineColor(itemAccentColor(i));
            itemName[i]->setFillColor(itemAccentColor(i));
            buyBtnBg[i].setFillColor(sf::Color(70, 110, 210));
        }
        else
        {
            cardBg[i].setFillColor(sf::Color(30, 30, 50));
            cardHighlight[i].setOutlineColor(sf::Color::Transparent);
            itemName[i]->setFillColor(sf::Color::White);
            buyBtnBg[i].setFillColor(sf::Color(50, 80, 160));
        }
    }
}

void ShopScreen::updateGemDisplay()
{
    if (gems[activePlayer] != nullptr)
        gemText.setString("Gems: " + to_string(gems[activePlayer]->getGems()));
}

int ShopScreen::getOwnedCount(int index) const
{
    switch (index)
    {
    case 0: return powerUps->getExtraLifeOwned();
    case 1: return powerUps->getSpeedBoostOwned();
    case 2: return powerUps->getDoubleScoreOwned();
    case 3: return powerUps->getWiderShotOwned();
    default: return 0;
    }
}

void ShopScreen::incrementOwned(int index)
{
    switch (index)
    {
    case 0: powerUps->incrementExtraLife();   break;
    case 1: powerUps->incrementSpeedBoost();  break;
    case 2: powerUps->incrementDoubleScore(); break;
    case 3: powerUps->incrementWiderShot();   break;
    }
}

void ShopScreen::activateFlag(int index)
{
    switch (index)
    {
    case 1: powerUps->setSpeedBoost(true);  break;
    case 2: powerUps->setDoubleScore(true); break;
    case 3: powerUps->setWiderShot(true);   break;
        // index 0 = Extra Life — no persistent flag, handled via owned count
    }
}

sf::Color ShopScreen::itemAccentColor(int index) const
{
    switch (index)
    {
    case 0: return sf::Color(255, 100, 100);  // Red   — Extra Life
    case 1: return sf::Color(100, 200, 255);  // Blue  — Speed Boost
    case 2: return sf::Color(255, 215, 0);  // Gold  — Double Score
    case 3: return sf::Color(100, 255, 160);  // Green — Wide Shot
    default: return sf::Color::White;
    }
}

// buildItems / buildCards — kept as stubs; all setup is in the constructor.
void ShopScreen::buildItems() {}
void ShopScreen::buildCards() {}