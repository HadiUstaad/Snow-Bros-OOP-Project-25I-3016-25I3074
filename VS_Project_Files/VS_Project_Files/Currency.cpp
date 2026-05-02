#include "Currency.h"


Currency::Currency()
{
    gems = 0;
    totalEarned = 0;
}


void Currency::addGems(int amount)
{
    if (amount <= 0)
        return;

    gems += amount;
    totalEarned += amount;
}


bool Currency::spendGems(int amount)
{
    // cant spend what you dont have
    if (amount > gems)
    {
        return false;
    }

    gems -= amount;
    return true;
}


int Currency::getGems() const
{
    return gems;
}


int Currency::getTotalEarned() const
{
    return totalEarned;
}


void Currency::reset()
{
    gems = 0;
    totalEarned = 0;
}


void Currency::setGems(int amount)
{
    if (amount >= 0)
    {
        gems = amount;
    }
}