#pragma once

class Display {
protected:
    bool isVisible;         // dipslay is visible
    bool isPaused;          // game paused

public:
    
    Display(bool pausesGame);

    
    virtual ~Display();

    // as menu shop login all screen are differencr so it is virtual abstract
    virtual void draw() = 0;

    // each display uses different input so pure virtual
    virtual void handleInput() = 0;

    void show();
    void hide();
    bool getIsVisible();
    bool getPaused();
};