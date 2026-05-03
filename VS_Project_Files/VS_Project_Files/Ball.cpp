#include"Ball.h"

Ball::Ball() {

	ball.setRadius(10.0);
	ball.setFillColor(sf::Color::White);
	//speed = 0.7f;
	velocityX = 0;
	velocityY = 0;
	active = false;
}

void Ball::shoot(float x, float y, int direction) {

	ball.setPosition({ x,y });
	//speed = 0.7f * direction;
	velocityX = 500.0f * direction;  // speed
	velocityY = -85.0f;             //  slight upward arc
	active = true;
}

void Ball::update(float deltaTime) {

	if (!active) {
		return;
	}

	//ball.move({ speed,0 });
	// gravity (optional but makes it feel like projectile)
	velocityY += 200.0f * deltaTime;

	// movement
	ball.move({ velocityX * deltaTime, velocityY * deltaTime });

	
	sf::Vector2f pos = ball.getPosition();
	float r = ball.getRadius();

	if (pos.x - r < 0 || pos.x + r > 800 ||
		pos.y - r < 0 || pos.y + r > 600)
	{
		active = false;
	}
}

void Ball::draw(sf::RenderWindow& window) {
	if (active) {
		window.draw(ball);
	}
}

bool Ball::checkactive() {
	return active;
}

sf::FloatRect Ball::getbounds() {
	return ball.getGlobalBounds();
}


