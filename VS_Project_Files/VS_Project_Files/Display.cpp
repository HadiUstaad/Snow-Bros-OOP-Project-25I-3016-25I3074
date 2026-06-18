#include "Display.h"

using namespace std;

Display::Display(bool pausesGame) 
{
    isVisible = true;         // Display will be visible by default
    isPaused = pausesGame;
}

// nothing right now. 
Display::~Display() {
    
}

void Display::show() {
    isVisible = true;
}

void Display::hide() {
    isVisible = false;
}

bool Display::getIsVisible() {
    return isVisible;
}

bool Display::getPaused() {
    return isPaused;
}
