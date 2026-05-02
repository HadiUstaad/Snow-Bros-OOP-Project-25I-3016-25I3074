#pragma once

// keeps track of the gem currency for one player
// gems are earned by killing enemies and spent in the shop
class Currency
{
private:
    int gems;           // current gem total
    int totalEarned;    // lifetime gems earned (for stats)

public:
    Currency();

    // add gems. called when enemy dies or boss defeated
    void addGems(int amount);

    // returns false if not enough gems
    bool spendGems(int amount);

    int getGems() const;
    int getTotalEarned() const;

    void reset();

    void setGems(int amount);
};