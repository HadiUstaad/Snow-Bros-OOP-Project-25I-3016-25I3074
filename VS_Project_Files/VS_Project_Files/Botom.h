#pragma once

#include <SFML/Graphics.hpp>
#include "GroundEnemy.h"

using namespace std;


class Boton : public GroundEnemy
{
private:
    int moveDirection; // 1 for right, -1 for left
    sf::RectangleShape shape; 

public:
    

    Boton(float x, float y);

    ~Boton() override = default;


    // If we don't override these, Boton remains abstract and we can't spawn it
    void updateMovement(float deltaTime) override; // From Enemies
    void draw() override;                          // From GameObject
    void draw(sf::RenderWindow& window);

};