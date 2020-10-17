#include "GameState.h"
#include "Entity.h"

GameState::GameState() {
	mapImage.load("images/map1.png");
	map = MapBuilder().createMap(mapImage);
	}
void GameState::tick() {
	map->tick();
	if(map->getGameStop()){ //change to GameOverState once it detects the game is over
		setFinished(true);
		setNextState("GameOver");
	}
}
void GameState::render() {
	map->render();
}

void GameState::keyPressed(int key){
	map->keyPressed(key);
}

void GameState::mousePressed(int x, int y, int button){
	map->mousePressed(x, y, button);
}

void GameState::keyReleased(int key){
	map->keyReleased(key);
}

void GameState::reset(){
	setFinished(false);
	setNextState("");
}
void GameState::resetMap(){ //replaces old map with new map
	mapImage.load("images/map1.png");
	map = MapBuilder().createMap(mapImage);
}