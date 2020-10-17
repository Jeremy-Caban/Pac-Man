#include "Map.h"
#include "GameOverState.h"

Map::Map(EntityManager* em){
    entityManager = em;
}

void Map::tick(){
	if (!gameStop)
	{
		entityManager->tick();
		player->tick();
	}
	if (player->getHealth() == 0)
	{
		this->gameStop = true;
	}else if(player->getHealth() > 0){
		this->gameStop = false;
	}
	
	
}
void Map::render(){
    ofSetBackgroundColor(0, 0, 0);
	entityManager->render();
	player->render();
	
}

void Map::keyPressed(int key){
	player->keyPressed(key);
	//-------------------------
	if(key == ' '){ //will reset the game
		this->gameStop = false;
	}
	//-------------------------
}

void Map::mousePressed(int x, int y, int button){
	player->mousePressed(x, y, button);
}

void Map::keyReleased(int key){
	player->keyReleased(key);
}
void Map::addBlock(Block* e){
    entityManager->blocks.push_back(e);
}
void Map::addEntity(Entity* e){
	entityManager->entities.push_back(e);
}
void Map::setPlayer(Player* p){
    player = p;
}

