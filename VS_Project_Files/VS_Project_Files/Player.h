#pragma once
#include"Input.h"
#include"Platform.h"
#include<SFML/Graphics.hpp>
class Player {

private:
	float x, y;
	float vx, vy;
	float speed;
	float gravity;
	float jumpforce;
	int jumpBuffer;

	bool onground;
	
	sf::RectangleShape Body;

public:
	Player();
	//Inputmanager remaining
	void update(Input& input, platform platforms[], int count);
	void draw(sf::RenderWindow& window);
	void drawHitbox(sf::RenderWindow& window);
	sf::FloatRect getBounds();
	void Reset();
};