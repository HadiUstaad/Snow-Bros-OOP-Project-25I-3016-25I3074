#pragma once
#include "Boss.h"
#include <SFML/Graphics.hpp>

using namespace std;



class Mogera : public Boss
{
private:
    sf::RectangleShape shape;      
    int childCount;            
    int maxChildPerPhase;       
    float spawnTimer;               //interval after they will spawn

public:
    
    Mogera(float x, float y);


    ~Mogera() override {}

    void updatePhase(float deltaTime) override;

    void spawnMinions() override;

    void draw(sf::RenderWindow&window) override;

};