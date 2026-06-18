#pragma once
#include "PowerUp.h"
#include <SFML/Graphics.hpp>

using namespace std;

class ExtraLife : public PowerUp
{

public:
    ExtraLife(float x, float y, bool dropped);
    ~ExtraLife() override = default;
};