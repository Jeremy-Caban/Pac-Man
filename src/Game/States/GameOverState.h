#pragma once

#include "State.h"
#include "MapBuilder.h"

class GameOverState : public State {
private:
	Map* m; //map has valueable info like health and score

public:
	GameOverState();
	void tick();
	void render();
	void keyPressed(int key);
	void mousePressed(int x, int y, int button);
	void reset();
	void setMap(Map* newMap){ m = newMap;}
};


