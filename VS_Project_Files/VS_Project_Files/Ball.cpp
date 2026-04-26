#include"Ball.h"

Ball::Ball() {

	ball.setRadius(20.0);
	ball.setFillColor(sf::Color::White);
	speed = 0.7f;
	active = false;
}

void Ball::shoot(float x, float y, int direction) {

	ball.setPosition({ x,y });
	speed = 0.7f * direction;
	active = true;
}

void Ball::update() {

	if (!active) {
		return;
	}

	ball.move({ speed,0 });

	if (ball.getPosition().x < 0 || ball.getPosition().x > 800) {
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


