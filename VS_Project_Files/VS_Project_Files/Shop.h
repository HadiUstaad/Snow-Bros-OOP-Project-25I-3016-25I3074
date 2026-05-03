#pragma once
#include "Display.h"
#include "Currency.h"
#include <SFML/Graphics.hpp>
#include <string>
using namespace std;

// ─────────────────────────────────────────────────────────────────────────────
// PowerUpState
// Holds all active power-up flags and owned counts for the session.
// Lives as a member in Game.h and passed by pointer to ShopScreen.
// ─────────────────────────────────────────────────────────────────────────────
class PowerUpState
{
private:
    bool speedBoost;
    bool doubleScore;
    bool widerShot;

    int  extraLifeOwned;
    int  speedBoostOwned;
    int  doubleScoreOwned;
    int  widerShotOwned;

public:
    PowerUpState();

    // Setters
    void setSpeedBoost(bool val);
    void setDoubleScore(bool val);
    void setWiderShot(bool val);

    void incrementExtraLife();
    void incrementSpeedBoost();
    void incrementDoubleScore();
    void incrementWiderShot();

    // Getters — flags
    bool getSpeedBoost()  const;
    bool getDoubleScore() const;
    bool getWiderShot()   const;

    // Getters — owned counts
    int getExtraLifeOwned()   const;
    int getSpeedBoostOwned()  const;
    int getDoubleScoreOwned() const;
    int getWiderShotOwned()   const;

    void reset();
};


// ─────────────────────────────────────────────────────────────────────────────
// ShopItem
// Pure data class — no SFML dependency.
// ─────────────────────────────────────────────────────────────────────────────
class ShopItem
{
private:
    string name;
    string description;
    string flavorText;
    int    cost;
    int    maxOwned;   // 0 = unlimited

public:
    ShopItem();
    ShopItem(const string& n, const string& desc,
        const string& flavor, int cost, int maxOwned);

    string getName()        const;
    string getDescription() const;
    string getFlavorText()  const;
    int    getCost()        const;
    int    getMaxOwned()    const;
};


// ─────────────────────────────────────────────────────────────────────────────
// ShopScreen
//
// SFML 3 NOTE:
//   sf::Text has NO default constructor — it must be constructed with a font.
//   Therefore all per-item sf::Text objects are stored as RAW POINTERS and
//   allocated in the constructor body after the font has been loaded.
//   The destructor deletes every pointer to prevent memory leaks.
// ─────────────────────────────────────────────────────────────────────────────
class ShopScreen : public Display
{
public:
    ShopScreen(sf::RenderWindow& gameWindow,
        Currency* p1Gems, Currency* p2Gems,
        PowerUpState* state);
    ~ShopScreen() override;

    void draw()        override;
    void handleInput() override;

    bool wasPurchased();
    int  lastPurchasedIndex();
    void resetPurchaseFlag();
    void setActivePlayer(int p);   // 0 = P1, 1 = P2

private:
    static const int ITEM_COUNT = 4;

    sf::RenderWindow& window;
    Currency* gems[2];     // [0]=P1  [1]=P2
    PowerUpState* powerUps;

    // Font must be declared BEFORE any sf::Text members that reference it
    sf::Font font;

    // ── Panel / layout ────────────────────────────────────────────────────
    sf::RectangleShape overlay;
    sf::RectangleShape panel;
    sf::RectangleShape headerBar;
    sf::RectangleShape accentLine;
    sf::RectangleShape footerLine;

    // ── Header / HUD text  (constructed with font in initialiser list) ────
    sf::Text  titleText;
    sf::Text  gemText;
    sf::Text  playerTag;
    sf::Text  backHint;
    sf::Text  feedbackText;
    sf::Clock feedbackTimer;
    bool      showFeedback;

    // ── Per-item card shapes (plain arrays — default-constructible) ───────
    sf::RectangleShape cardBg[ITEM_COUNT];
    sf::RectangleShape cardBorder[ITEM_COUNT];    // coloured left strip
    sf::RectangleShape cardHighlight[ITEM_COUNT]; // selection outline
    sf::CircleShape    itemIcon[ITEM_COUNT];
    sf::RectangleShape buyBtnBg[ITEM_COUNT];

    // ── Per-item text  (POINTERS — allocated after font loads) ───────────
    sf::Text* itemName[ITEM_COUNT];
    sf::Text* itemDesc[ITEM_COUNT];
    sf::Text* itemFlavor[ITEM_COUNT];
    sf::Text* itemCost[ITEM_COUNT];
    sf::Text* itemOwned[ITEM_COUNT];
    sf::Text* buyBtnText[ITEM_COUNT];

    // ── State ─────────────────────────────────────────────────────────────
    int      selected;
    int      activePlayer;
    bool     purchaseFlag;
    int      lastBought;

    ShopItem items[ITEM_COUNT];

    // ── Private helpers ───────────────────────────────────────────────────
    void buildItems();
    void buildCards();
    void updateCardStyles();
    void updateGemDisplay();
    void tryBuy(int index);

    int  getOwnedCount(int index) const;
    void incrementOwned(int index);
    void activateFlag(int index);

    sf::Color itemAccentColor(int index) const;
};
