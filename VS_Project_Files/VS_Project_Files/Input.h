#pragma once
#include<SFML/Graphics.hpp>
class Input {
public:
	bool left;
	bool right;
	
	bool jump;
	bool jumppressed;

	bool left1;
	bool right1;
	bool jump1;
	void updatePlayer1();
	void updatePlayer2();
};