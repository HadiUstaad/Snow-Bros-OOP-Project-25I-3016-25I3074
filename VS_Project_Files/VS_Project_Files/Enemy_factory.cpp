#include "Enemy_factory.h"
#include <ctime>

// Creates enemy based on type code at specified position
Enemies* EnemyCreator::createEnemy(int type, float x, float y)
{
    // Create different enemy based on type
    if (type == 0)
    {
        return new Boton(x, y);
    }
    else if (type == 1)
    {
        return new Fooga(x, y);
    }
    else if (type == 2)
    {
        return new Tornado(x, y);
    }
    else if (type == 3)
    {
        return new Mogera(x, y);
    }
    else
    {
        return new Boton(x, y);
    }
}

// Determines which enemy type should spawn based on level
int EnemyCreator::getEnemyType(int level)
{
    // Level 1-2 only Boton
    // Level 3-4 Boton and Fooga
    // Level 5 is Mogera boss
    // Level 6-9 all regular enemies
    // Level 10 final boss

    srand(time(0));
    if (level <= 2)
    {
        return 0;   
    }   
    else if (level <= 4)
    {
        if (rand() % 2 == 0)
            return 1;   // Fooga
        else
            return 0;   // Boton
    }   
    else if (level == 5)
    {
        return 3;   // Mogera boss
    }
    else if (level <= 9)
    {
        if ((rand() % 3 == 0))
            return 0;   // Boton
        else if (rand() % 3 == 1)
            return 1;   // Fooga
        else if(rand() % 3 == 2)
            return 2;   // Tornado
    }
    else
    {
        return 3;  //gamakichi
    }
}

// Gets color variants for stronger enemies
int EnemyCreator::getColor(int baseType)
{
    // Color variants: 0 = normal, 1 = red (1.5x), 2 = blue (2x) as lvl increase
    // Future implementation would create wrapped enemy with multipliers
    // For now just return normal
    return 0;
}