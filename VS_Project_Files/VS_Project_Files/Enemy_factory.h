#pragma once
#include "Enemy.h"
#include "Botom.h"
#include "Fooga.h"
#include "Tornado.h"
#include "Mogera.h"

using namespace std;

// auto creates enemies
class EnemyCreator
{
public:
    
    //  0= Boton, 1 =Fooga, 2 = Tornado, 3 =Mogera
    static Enemies* createEnemy(int type, float x, float y);

    // each level has its own enemy types
    static int getEnemyType(int level);

    // different colors
    static int getColor(int baseType);
};