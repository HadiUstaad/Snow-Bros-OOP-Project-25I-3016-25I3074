#pragma once

#include <SFML/Graphics.hpp>
#include "GroundEnemy.h"
#include "Platform.h"

using namespace std;


class Boton : public GroundEnemy
{
    private:
    int moveDirection; // 1 for right, -1 for left
    sf::RectangleShape shape; 
    bool froze;
    bool alive;

public:
    
   
    sf::FloatRect getBounds();
    Boton(float x, float y);

    ~Boton() override = default;


    // If we don't override these, Boton remains abstract and we can't spawn it
    void updateMovement(float deltaTime,platform platform[], int count) override; // From Enemies
    
    void draw(sf::RenderWindow& window);

    void freeze();
    bool checkfreeze();
};