#include"Player.h"
#include"Input.h"
#include"Platform.h"
#include<SFML/Graphics.hpp>
#include<iostream>

using namespace std;


static const float PLAYER_FRAME_X = 20;    // column index of idle first frame
static const float PLAYER_FRAME_Y = 4;    //  row index of idle frame  
static const float PLAYER_FRAME_WIDTH = 55;  // width of one frame in sheet
static const float PLAYER_FRAME_HEIGHT = 75;  //  height of one frame in sheet
Player::Player() : texture(), sprite(texture) {


	isAlive = true;


	x = 100;
	y = 300;

	vx = 0;
	vy = 0;

	speed = 0.5;
	gravity = 0.12f;
	jumpforce = -7.0f;
	jumpBuffer = 0;

	direction = 1;

	onground = false;

	Body.setSize({ 50,50 });
	Body.setFillColor(sf::Color::Transparent);

	
	if (!texture.loadFromFile("SnowBrosAssets/Images/Player_Red.png")) 
	{
		cout << "Player texture failed to load\n";
	}
	else 
	{
		cout << "Player texture loaded\n";
	}
	
	// according to frame width hight the sprite coords ko fix kiya hai
	frameRect = sf::IntRect(sf::Vector2i(PLAYER_FRAME_X, PLAYER_FRAME_Y),
		sf::Vector2i(PLAYER_FRAME_WIDTH, PLAYER_FRAME_HEIGHT));

	sprite = sf::Sprite(texture, frameRect); //use rectangular framme

	
	float scaleX = 50 / PLAYER_FRAME_WIDTH;
	float scaleY = 50 /PLAYER_FRAME_HEIGHT;
	sprite.setScale({ scaleX, scaleY });
	
}

// diff sheet for both player
void Player::loadTexture(const string& file)
{
	if (!texture.loadFromFile(file)) {
		cout << "Player texture failed: " << file << "\n";
		return;
	}

	// same logic as in constructor
	// re apply frame rect after loading new texture
	frameRect = sf::IntRect(sf::Vector2i(PLAYER_FRAME_X, PLAYER_FRAME_Y),
		sf::Vector2i(PLAYER_FRAME_WIDTH, PLAYER_FRAME_HEIGHT));
	sprite.setTexture(texture);
	sprite.setTextureRect(frameRect);

	float scaleX = 50.0f / PLAYER_FRAME_WIDTH;
	float scaleY = 50.0f / PLAYER_FRAME_HEIGHT;
	sprite.setScale({ scaleX, scaleY });
}
void Player::update(Input& input, platform platforms[], int count) {


	if (!isAlive)
	{
		return;
	}
	vx = 0;

	//left movement
	if (input.left) {
		vx = -speed;
		direction = -1;
	}
	//right movement
	if (input.right) {
		vx = speed;
		direction = 1;
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
	sprite.setPosition({ x,y });

	sf::FloatRect playerBounds = Body.getGlobalBounds();



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

	// flip sprite based on direction
	if (direction == 1) 
	{
		// - is the flip in setscale.
		// + 50 in set position to avoid the ajeeb sa change jo ho raha tha
		sprite.setScale({ -50.0f / PLAYER_FRAME_WIDTH, 50.0f / PLAYER_FRAME_HEIGHT });
		sprite.setPosition({ x + 50, y }); 
	}
	else 
	{
		sprite.setScale({ 50.0f / PLAYER_FRAME_WIDTH, 50.0f / PLAYER_FRAME_HEIGHT });
		sprite.setPosition({ x, y });
	}
}


//character draw
void Player::draw(sf::RenderWindow& window) 
{
	if (isAlive)
	{
		window.draw(sprite);

	}
	
}



//Hit boxes
void Player::drawHitbox(sf::RenderWindow& window) 
{
	if (isAlive)
	{

		sf::RectangleShape box;
		box.setSize(Body.getSize());
		box.setPosition(Body.getPosition());
		box.setFillColor(sf::Color::Transparent);
		box.setOutlineColor(sf::Color::Green);
		box.setOutlineThickness(3);

		window.draw(box);
	}
}


sf::FloatRect Player::getBounds() {
	if (!isAlive)
	{
		//enemy projectile woont hit
		return sf::FloatRect({ 0, 0 }, { 0, 0 });
	}
	return Body.getGlobalBounds();
}

void Player::Reset() {
	
	x = 100;
	y = 300;
	vx = 0;
	vy = 0;

	Body.setPosition({ x, y });
}

void Player::setPosition(float x, float y)
{
	this->x = x;
	this->y = y;
	Body.setPosition({ x, y });
}


int Player::getDirection() {
	return direction;
}

void Player::die() {
	isAlive = false;
}

void Player::revive() {
	isAlive = true;
	Reset();
}

bool Player::getIsAlive() const {
	return isAlive;
}
