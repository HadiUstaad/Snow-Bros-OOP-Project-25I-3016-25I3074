#pragma once
#include"Input.h"
#include<string>
#include"Platform.h"
#include<SFML/Graphics.hpp>
using namespace std;

class Player {

private:
	float x, y;
	float vx, vy;
	float speed;
	float gravity;
	float jumpforce;
	int jumpBuffer;

	int direction;
	bool onground;

	bool isAlive;
	

	sf::Texture texture;
	sf::Sprite sprite;
	sf::IntRect frameRect;

	sf::RectangleShape Body;	// collision logic
public:
	Player();
	
	void update(Input& input, platform platforms[], int count);
	void draw(sf::RenderWindow& window);
	void drawHitbox(sf::RenderWindow& window);
	sf::FloatRect getBounds();
	void Reset();
	void setPosition(float x, float y);
	int getDirection();
	void loadTexture(const string& file);

	void die();

	void revive();
	bool getIsAlive() const;

};