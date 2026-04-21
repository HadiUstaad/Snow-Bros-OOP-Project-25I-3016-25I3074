#pragma once
#include"Input.h"
#include<SFML/Graphics.hpp>
class Player {

private:
	float x, y;
	float vx, vy;
	float speed;
	float gravity;
	float jumpforce;

	bool onground;
	
	sf::RectangleShape Body;

public:
	Player();
	//Inputmanager remaining
	void update(Input& input);
	void draw(sf::RenderWindow& window);
};