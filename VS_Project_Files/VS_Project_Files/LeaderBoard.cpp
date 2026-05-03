
#include "LeaderBoard.h"
#include <string>
#include <iostream>
#include <iomanip>
#include <sstream>
using namespace std;

// ─── Colour palette ──────────────────────────────────────────────────────────
static const sf::Color COL_BG_PANEL(10, 12, 28, 230);   // deep navy
static const sf::Color COL_HEADER_BAR(20, 24, 55, 255);   // slightly lighter navy
static const sf::Color COL_ACCENT(0, 229, 255, 255);   // cyan accent
static const sf::Color COL_GOLD(255, 215, 0, 255);
static const sf::Color COL_SILVER(192, 192, 192, 255);
static const sf::Color COL_BRONZE(205, 127, 50, 255);
static const sf::Color COL_NORMAL(180, 200, 255, 255);   // soft blue-white
static const sf::Color COL_EMPTY(80, 90, 120, 255);   // muted grey
static const sf::Color COL_ROW_ODD(255, 255, 255, 8);   // very subtle stripe
static const sf::Color COL_ROW_EVEN(0, 0, 0, 0);
static const sf::Color COL_SEPARATOR(60, 70, 110, 180);

// Window & layout constants (tweak to fit your resolution)
static const float WIN_W = 800.f;
static const float WIN_H = 600.f;
static const float PANEL_X = 80.f;
static const float PANEL_Y = 30.f;
static const float PANEL_W = WIN_W - PANEL_X * 2.f;   // 640
static const float PANEL_H = WIN_H - PANEL_Y * 2.f;   // 540
static const float HEADER_H = 70.f;
static const float COL_H = 36.f;    // column-header row height
static const float ROW_H = 42.f;   // each data row
static const float ROWS_Y = PANEL_Y + HEADER_H + COL_H + 8.f;
static const float RANK_X = PANEL_X + 20.f;
static const float NAME_X = PANEL_X + 100.f;
static const float SCORE_X = PANEL_X + PANEL_W - 20.f;  // right-aligned

// ─── Helpers ─────────────────────────────────────────────────────────────────
sf::Color LeaderboardScreen::getRankColor(int rank) const
{
    switch (rank)
    {
    case 1:  return COL_GOLD;
    case 2:  return COL_SILVER;
    case 3:  return COL_BRONZE;
    default: return COL_NORMAL;
    }
}

sf::Color LeaderboardScreen::getRankBadgeColor(int rank) const
{
    // translucent tinted circle behind the rank number
    switch (rank)
    {
    case 1:  return sf::Color(255, 215, 0, 45);
    case 2:  return sf::Color(192, 192, 192, 45);
    case 3:  return sf::Color(205, 127, 50, 45);
    default: return sf::Color(60, 70, 110, 60);
    }
}

static string formatScore(int score)
{
    // insert commas: 98450 -> "98,450"
    string s = to_string(score);
    int insertPos = (int)s.size() - 3;
    while (insertPos > 0) { s.insert(insertPos, ","); insertPos -= 3; }
    return s;
}

// ─── Constructor ─────────────────────────────────────────────────────────────
LeaderboardScreen::LeaderboardScreen(sf::RenderWindow& gameWindow, FileManage* fm)
    : Display(true),
    window(gameWindow),
    titleText(font),
    colRank(font), colName(font), colScore(font),
    back(font)
{
    fileManager = fm;

    if (!font.openFromFile("RussoOne-Regular.ttf"))
        cout << "Error: Cannot load font 'RussoOne-Regular.ttf'\n";

    // ── Allocate per-row objects ────────────────────────────────────────────
    for (int i = 0; i < 10; i++)
    {
        RanksTexts[i] = new sf::Text(font);
        nameTexts[i] = new sf::Text(font);
        scoreTexts[i] = new sf::Text(font);
        rowBgs[i] = new sf::RectangleShape();
        rankBadges[i] = new sf::CircleShape(16.f);
        leaderboardUserNames[i] = "";
        leaderboardScores[i] = 0;
    }

    // ── Background panel ───────────────────────────────────────────────────
    bgPanel.setSize(sf::Vector2f(PANEL_W, PANEL_H));
    bgPanel.setPosition(sf::Vector2f(PANEL_X, PANEL_Y));
    bgPanel.setFillColor(COL_BG_PANEL);
    bgPanel.setOutlineThickness(1.5f);
    bgPanel.setOutlineColor(COL_ACCENT);

    // ── Header bar ─────────────────────────────────────────────────────────
    headerBar.setSize(sf::Vector2f(PANEL_W, HEADER_H));
    headerBar.setPosition(sf::Vector2f(PANEL_X, PANEL_Y));
    headerBar.setFillColor(COL_HEADER_BAR);

    // ── Accent line under title ─────────────────────────────────────────────
    accentLine.setSize(sf::Vector2f(80.f, 3.f));
    accentLine.setFillColor(COL_ACCENT);
    accentLine.setPosition(sf::Vector2f(PANEL_X + PANEL_W / 2.f - 40.f,
        PANEL_Y + HEADER_H - 6.f));

    // ── Title ───────────────────────────────────────────────────────────────
    titleText.setFont(font);
    titleText.setString("LEADERBOARD");
    titleText.setCharacterSize(30);
    titleText.setFillColor(sf::Color::White);
    titleText.setLetterSpacing(3.f);
    {
        sf::FloatRect b = titleText.getLocalBounds();
        titleText.setOrigin(sf::Vector2f(b.size.x / 2.f, b.size.y / 2.f));
        titleText.setPosition(sf::Vector2f(PANEL_X + PANEL_W / 2.f,
            PANEL_Y + HEADER_H / 2.f - 4.f));
    }

    // ── Column headers ──────────────────────────────────────────────────────
    float colY = PANEL_Y + HEADER_H + 6.f;

    colRank.setFont(font);
    colRank.setString("#");
    colRank.setCharacterSize(13);
    colRank.setFillColor(COL_ACCENT);
    colRank.setLetterSpacing(2.f);
    colRank.setPosition(sf::Vector2f(RANK_X, colY));

    colName.setFont(font);
    colName.setString("PLAYER");
    colName.setCharacterSize(13);
    colName.setFillColor(COL_ACCENT);
    colName.setLetterSpacing(2.f);
    colName.setPosition(sf::Vector2f(NAME_X, colY));

    colScore.setFont(font);
    colScore.setString("SCORE");
    colScore.setCharacterSize(13);
    colScore.setFillColor(COL_ACCENT);
    colScore.setLetterSpacing(2.f);
    {
        sf::FloatRect b = colScore.getLocalBounds();
        colScore.setOrigin(sf::Vector2f(b.size.x, 0.f));
        colScore.setPosition(sf::Vector2f(SCORE_X, colY));
    }

    // Separator under column headers
    headerSep.setSize(sf::Vector2f(PANEL_W - 20.f, 1.f));
    headerSep.setFillColor(COL_SEPARATOR);
    headerSep.setPosition(sf::Vector2f(PANEL_X + 10.f,
        colY + 22.f));

    // ── Footer ──────────────────────────────────────────────────────────────
    footerLine.setSize(sf::Vector2f(PANEL_W - 20.f, 1.f));
    footerLine.setFillColor(COL_SEPARATOR);
    footerLine.setPosition(sf::Vector2f(PANEL_X + 10.f,
        PANEL_Y + PANEL_H - 38.f));

    back.setFont(font);
    back.setString("[ ESC ]  GO BACK");
    back.setCharacterSize(14);
    back.setLetterSpacing(2.f);
    back.setFillColor(sf::Color(140, 160, 200, 200));
    {
        sf::FloatRect b = back.getLocalBounds();
        back.setOrigin(sf::Vector2f(b.size.x / 2.f, 0.f));
        back.setPosition(sf::Vector2f(PANEL_X + PANEL_W / 2.f,
            PANEL_Y + PANEL_H - 30.f));
    }

    // ── Build row visuals ───────────────────────────────────────────────────
    for (int i = 0; i < 10; i++)
        buildRow(i);

    updateLeaderboard();
}

// ─── buildRow ────────────────────────────────────────────────────────────────
void LeaderboardScreen::buildRow(int i)
{
    float rowY = ROWS_Y + i * ROW_H;
    int   rank = i + 1;

    // Row background stripe
    rowBgs[i]->setSize(sf::Vector2f(PANEL_W - 2.f, ROW_H - 2.f));
    rowBgs[i]->setPosition(sf::Vector2f(PANEL_X + 1.f, rowY + 1.f));
    rowBgs[i]->setFillColor(i % 2 == 0 ? COL_ROW_ODD : COL_ROW_EVEN);

    // Rank badge circle
    rankBadges[i]->setRadius(16.f);
    rankBadges[i]->setOrigin(sf::Vector2f(16.f, 16.f));
    rankBadges[i]->setPosition(sf::Vector2f(RANK_X + 16.f, rowY + ROW_H / 2.f));
    rankBadges[i]->setFillColor(getRankBadgeColor(rank));
    rankBadges[i]->setOutlineThickness(rank <= 3 ? 1.f : 0.f);
    rankBadges[i]->setOutlineColor(getRankColor(rank));

    // Rank number text
    RanksTexts[i]->setFont(font);
    RanksTexts[i]->setString(to_string(rank));
    RanksTexts[i]->setCharacterSize(15);
    RanksTexts[i]->setFillColor(getRankColor(rank));
    {
        sf::FloatRect b = RanksTexts[i]->getLocalBounds();
        RanksTexts[i]->setOrigin(sf::Vector2f(b.size.x / 2.f, b.size.y / 2.f));
        RanksTexts[i]->setPosition(sf::Vector2f(RANK_X + 16.f, rowY + ROW_H / 2.f - 2.f));
    }

    // Player name text
    nameTexts[i]->setFont(font);
    nameTexts[i]->setCharacterSize(16);
    nameTexts[i]->setPosition(sf::Vector2f(NAME_X, rowY + (ROW_H - 18.f) / 2.f));

    // Score text (right-aligned)
    scoreTexts[i]->setFont(font);
    scoreTexts[i]->setCharacterSize(16);
    scoreTexts[i]->setPosition(sf::Vector2f(SCORE_X, rowY + (ROW_H - 18.f) / 2.f));
}

// ─── Destructor ──────────────────────────────────────────────────────────────
LeaderboardScreen::~LeaderboardScreen()
{
    for (int i = 0; i < 10; i++)
    {
        delete RanksTexts[i];
        delete nameTexts[i];
        delete scoreTexts[i];
        delete rowBgs[i];
        delete rankBadges[i];
    }
}

// ─── draw ─────────────────────────────────────────────────────────────────────
void LeaderboardScreen::draw()
{
    if (!isVisible) return;

    // Panel
    window.draw(bgPanel);
    window.draw(headerBar);
    window.draw(accentLine);
    window.draw(titleText);

    // Column headers
    window.draw(colRank);
    window.draw(colName);
    window.draw(colScore);
    window.draw(headerSep);

    // Rows
    for (int i = 0; i < 10; i++)
    {
        window.draw(*rowBgs[i]);
        window.draw(*rankBadges[i]);
        window.draw(*RanksTexts[i]);
        window.draw(*nameTexts[i]);
        window.draw(*scoreTexts[i]);
    }

    // Footer
    window.draw(footerLine);
    window.draw(back);
}

// ─── handleInput ─────────────────────────────────────────────────────────────
void LeaderboardScreen::handleInput()
{
    if (!isVisible) return;

    static sf::Clock inputTimer;
    if (inputTimer.getElapsedTime().asMilliseconds() < 300)
        return;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
    {
        isVisible = false;
        inputTimer.restart();
    }
}

// ─── updateLeaderboard ───────────────────────────────────────────────────────
void LeaderboardScreen::updateLeaderboard()
{
    fileManager->getTopScores(leaderboardUserNames, leaderboardScores);

    for (int i = 0; i < 10; i++)
    {
        int rank = i + 1;
        bool empty = leaderboardUserNames[i].empty();

        // --- Name ---
        if (empty)
        {
            nameTexts[i]->setString("--- N/L ---");
            nameTexts[i]->setFillColor(COL_EMPTY);
        }
        else
        {
            nameTexts[i]->setString(leaderboardUserNames[i]);
            nameTexts[i]->setFillColor(getRankColor(rank));
        }

        // --- Score ---
        if (empty || leaderboardScores[i] == 0)
        {
            scoreTexts[i]->setString("---");
            scoreTexts[i]->setFillColor(COL_EMPTY);
        }
        else
        {
            scoreTexts[i]->setString(formatScore(leaderboardScores[i]));
            scoreTexts[i]->setFillColor(getRankColor(rank));
        }

        // Right-align score
        {
            sf::FloatRect b = scoreTexts[i]->getLocalBounds();
            scoreTexts[i]->setOrigin(sf::Vector2f(b.size.x, 0.f));
        }

        // Rebuild rank badge origin (text width changes with rank number digits)
        {
            sf::FloatRect b = RanksTexts[i]->getLocalBounds();
            RanksTexts[i]->setOrigin(sf::Vector2f(b.size.x / 2.f, b.size.y / 2.f));
        }
    }
}
