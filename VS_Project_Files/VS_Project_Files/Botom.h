#pragma once

#include <SFML/Graphics.hpp>
#include "GroundEnemy.h"

using namespace std;


class Boton : public GroundEnemy
{
private:
    int moveDirection; // 1 for right, -1 for left
    sf::RectangleShape shape; // SFML visual representation

public:
    // Constructor for the Boton enemy
    Boton(float x, float y);

    ~Boton() override = default;

    // --- OVERRIDING PURE VIRTUAL FUNCTIONS ---
    // If we don't override these, Boton remains abstract and we can't spawn it!

    void updateMovement(float deltaTime) override; // From Enemies
    void draw() override;                          // From GameObject

    // SFML specific helper
    void draw(sf::RenderWindow& window);

};