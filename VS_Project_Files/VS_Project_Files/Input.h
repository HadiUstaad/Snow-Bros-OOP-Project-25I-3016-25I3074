#pragma once
#include<SFML/Graphics.hpp>
class Input {
public:
	bool left;
	bool right;
	
	bool jump;
	bool jumppressed;
	void update();
};