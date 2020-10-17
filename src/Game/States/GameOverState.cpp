#include "GameOverState.h"
#include "EntityManager.h"
#include "GameState.h"
GameOverState::GameOverState() {}

void GameOverState::tick() {
	
}
void GameOverState::render() {
	
    ofImage GameOver("images/Rage.jpg");
    GameOver.draw(ofGetWidth() * 0.05,ofGetHeight() * 0.05, ofGetWidth() * 0.9,ofGetHeight() * 0.9);
	//Display score
    ofDrawBitmapString("Score: " + to_string(m->getPlayer()->getScore()), ofGetWidth() * 0.47, ofGetHeight() / 4);
	//Display reset instructions
	ofDrawBitmapString("Press 'SPACE' to restart", ofGetWidth()*0.47 - 50, ofGetHeight()/2 + 300);

}

void GameOverState::keyPressed(int key){
	if(key == ' '){ // reset game by pressing "SPACE"
		setNextState("Game");
	 	setFinished(true);
	}
}

void GameOverState::mousePressed(int x, int y, int button){}

void GameOverState::reset(){
	setFinished(false);
	setNextState("");
}