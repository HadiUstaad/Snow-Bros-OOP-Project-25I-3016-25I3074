#include"Player.h"
#include"Input.h"
#include"Platform.h"
#include<SFML/Graphics.hpp>
Player::Player() {
	x = 100;
	y = 300;

	vx = 0;
	vy = 0;

	speed = 1.5;
	gravity = 0.1f;
	jumpforce = -5;

	onground = false;

	Body.setSize({ 50,50 });
	Body.setFillColor(sf::Color::Blue);
}

void Player::update(Input& input , platform& ground) {

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


	// screen size
	float screenWidth = 800;
	float screenHeight = 600;

	// get player size
	sf::Vector2f size = Body.getSize();

	// 🔹 LEFT boundary
	if (x < 0)
		x = 0;

	// 🔹 RIGHT boundary
	if (x + size.x > screenWidth)
		x = screenWidth - size.x;

	// 🔹 TOP boundary
	if (y < 0)
		y = 0;

	// 🔹 BOTTOM boundary (optional if using platform)
	if (y + size.y > screenHeight) {
		y = screenHeight - size.y;
		vy = 0;
		onground = true;
	}

	// apply corrected position
	Body.setPosition({ x, y });

	//on ground logic
	Body.setPosition({ x,y });

	onground = false;
	sf::FloatRect playerBounds = Body.getGlobalBounds();
	sf::FloatRect groundBounds = ground.getbody().getGlobalBounds();

	if (playerBounds.findIntersection(groundBounds)) {

		if (vy > 0) {

			float previousBottom = playerBounds.position.y + playerBounds.size.y - vy;

			if (previousBottom <= groundBounds.position.y + 2) { 

				y = groundBounds.position.y - playerBounds.size.y;
				vy = 0;
				onground = true;

				Body.setPosition({ x, y });
			}
		}
	}

}


//character draw
void Player::draw(sf::RenderWindow& window) {
	window.draw(Body);
}