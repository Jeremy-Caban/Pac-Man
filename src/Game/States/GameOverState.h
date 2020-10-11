#pragma once

#include "State.h"
//#include "Button.h"

class GameOverState : public State {
private:
	ofImage img2;
	//Button *resetButton;

public:
	GameOverState();
	int health = 3;//Pac Health
    int score = 0; //set score to 0
	void tick();
	void render();
	void keyPressed(int key);
	void mousePressed(int x, int y, int button);
	void reset();
};


