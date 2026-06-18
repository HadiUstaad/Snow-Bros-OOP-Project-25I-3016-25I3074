#pragma once
#pragma once
#include "GroundEnemy.h"
#include <SFML/Graphics.hpp>

using namespace std;

// small child enemy spawned by Mogera. moves in one direction toward player
class MogeraChild : public GroundEnemy
{
private:
    sf::RectangleShape shape;
    int moveDirection;      // 1 for right, -1 for left
    bool alive;
    bool froze;

    sf::Texture texture;
    sf::Sprite sprite;
    sf::IntRect frameRect;
public:
    MogeraChild(float x, float y, int direction);

    ~MogeraChild() override = default;

    void updateMovement(float deltaTime, platform platform[], int count) override;

    void draw(sf::RenderWindow& window) override;

    void drawHitbox(sf::RenderWindow& window) override;

    sf::FloatRect getBounds();

    void freeze();      // extra functions but still written bcz it is in other classes too
    bool checkfreeze();

    void onHit() override;
    bool isAlive() override;
};