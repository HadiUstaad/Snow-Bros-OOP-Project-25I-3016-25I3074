#include"Player.h"
#include"Input.h"
#include"Platform.h"
#include<SFML/Graphics.hpp>
Player::Player() {
	x = 100;
	y = 300;

	vx = 0;
	vy = 0;

	speed = 0.5;
	gravity = 0.1f;
	jumpforce = -5;
	jumpBuffer = 0;

	onground = false;

	Body.setSize({ 50,50 });
	Body.setFillColor(sf::Color::Blue);
}

void Player::update(Input& input, platform platforms[], int count) {

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

	if (input.jumppressed) {
		jumpBuffer = 8;   // buffer for few frames
	}
	if (jumpBuffer > 0 && onground) {
		vy = jumpforce;
		onground = false;
		jumpBuffer = 0;
	}

	if (jumpBuffer > 0)
		jumpBuffer--;
	//gravity
	if (!onground) {
		vy += gravity;
	}

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

	sf::FloatRect playerBounds = Body.getGlobalBounds();


	//	if (playerBounds.findIntersection(groundBounds)) {
	//
	//		if (vy > 0) {
	//
	//			float previousBottom = playerBounds.position.y + playerBounds.size.y - vy;
	//
	//			if (previousBottom <= groundBounds.position.y + 2) { 
	//
	//				y = groundBounds.position.y - playerBounds.size.y;
	//				vy = 0;
	//				onground = true;
	//
	//				Body.setPosition({ x, y });
	//			}
	//		}
	//	}
	//
	//}

	onground = false;

	for (int i = 0; i < count; i++) {

		sf::Vector2f pPos = Body.getPosition();
		sf::Vector2f pSize = Body.getSize();

		sf::Vector2f gPos = platforms[i].getBody().getPosition();
		sf::Vector2f gSize = platforms[i].getBody().getSize();

		bool collision =
			pPos.x < gPos.x + gSize.x &&
			pPos.x + pSize.x > gPos.x &&
			pPos.y < gPos.y + gSize.y &&
			pPos.y + pSize.y > gPos.y;

		if (collision && vy >= 0) {

			float previousBottom = pPos.y + pSize.y - vy;

			if (previousBottom <= gPos.y + 2) {

				y = gPos.y - pSize.y;
				vy = 0;
				onground = true;

				Body.setPosition({ x, y });
			}
		}
	}

	if (onground) {
		vy = 0;
	}
}


//character draw
void Player::draw(sf::RenderWindow& window) {
	window.draw(Body);
}



//Hit boxes
void Player::drawHitbox(sf::RenderWindow& window) {
	sf::RectangleShape box;
	box.setSize(Body.getSize());
	box.setPosition(Body.getPosition());
	box.setFillColor(sf::Color::Transparent);
	box.setOutlineColor(sf::Color::Green);
	box.setOutlineThickness(3);

	window.draw(box);
}