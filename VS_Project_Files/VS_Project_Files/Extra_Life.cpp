#include "Extra_Life.h"

// Constructor creates extra life powerup at position
ExtraLife::ExtraLife(float x, float y, bool dropped)
    : PowerUp(x, y, 0, 100, 1)  // instant effect costs 100 gems type 1
{
    isDroppedFromEnemy = dropped;

    shape.setFillColor(sf::Color::Red);         // red for life

}
