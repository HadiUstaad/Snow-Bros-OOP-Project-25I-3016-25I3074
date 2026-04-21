#include"Player.h"
#include"Input.h"
Player::Player() {
	x = 100;
	y = 300;

	vx = 0;
	vy = 0;

	speed = 2;
	gravity = 0.5f;
	jumpforce = -5;

	onground = false;

	Body.setSize({ 50,50 });
	Body.setFillColor(sf::Color::Blue);
}

void Player::update(Input& input) {

	vx = 0;

	//left movement
	if (input.left) {
		vx = -speed;
	}
	//right movement
	if (input.right) {
		vx = speed;
	}
	//jump move

	if (input.jump && onground) {
		vy = jumpforce;
		onground = false;
	}
	//gravity
	vy += gravity;

	//movement
	x += vx;
	y += vy;

	//on ground logic
	if (y >= 500) {
		y = 500;
		vy = 0;
		onground = true;
	}

	Body.setPosition({ x,y });
}


//character draw
void Player::draw(sf::RenderWindow& window) {
	window.draw(Body);
}