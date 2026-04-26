#pragma once
#include<SFML/Graphics.hpp>


class Ball {

private:
	sf::CircleShape ball;
	float speed;
	bool active;
	
public:
	Ball();
	void shoot(float x, float y, int direction);
	void update();
	void draw(sf::RenderWindow& window);


	bool checkactive();
	sf::FloatRect getbounds();
};