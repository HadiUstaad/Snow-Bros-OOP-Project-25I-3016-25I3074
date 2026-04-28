#pragma once
#include "Boss.h"
#include <SFML/Graphics.hpp>

using namespace std;

// modify to add snowball damage

class Mogera : public Boss
{
private:
    sf::RectangleShape shape;      
    int childCount;            
    int maxChildPerPhase;       
    float spawnTimer;               //interval after they will spawn

    bool alive;

public:
    
    Mogera(float x, float y);


    ~Mogera() override {}

    void updatePhase(float deltaTime) override;

    void spawnMinions() override;

    void draw(sf::RenderWindow&window) override;

    void drawHitbox(sf::RenderWindow& window) override;

    virtual void updateMovement(float deltaTime, platform platform[], int count);

    
    virtual void onHit();
    virtual bool isAlive();
};