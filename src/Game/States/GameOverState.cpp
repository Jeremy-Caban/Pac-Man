#include "GameOverState.h"
#include "Player.h"
#include "EntityManager.h"

GameOverState::GameOverState() {
	// resetButton = new Button(ofGetWidth() / 2, ofGetHeight() / 2, 900, 350, "Reset");
	
}
void GameOverState::tick() {
	// resetButton->tick();
	// if(resetButton->wasPressed()){
	 	//setNextState("Game");
	 	//setFinished(true);

	// }
}
void GameOverState::render() {
	
	if (this->health == 0)
    {
        
        ofImage GameOver("images/Rage.jpg");
        GameOver.draw(ofGetWidth() * 0.05,ofGetHeight() * 0.05, ofGetWidth() * 0.9,ofGetHeight() * 0.9);
        ofDrawBitmapString("Score: " + to_string(score), ofGetWidth() * 0.47, ofGetHeight() / 4);
    }
	//  ofImage GameBackground("images/ChasingPac.png");
	//  GameBackground.draw(0, 0,ofGetWidth(),ofGetHeight());
	// // ofImage resetButton("images/Start.jpg");
	// // resetButton.draw(830, 340, ofGetWidth() / 6, ofGetHeight() / 6);
}

void GameOverState::keyPressed(int key){
	
}

void GameOverState::mousePressed(int x, int y, int button){
	//resetButton->mousePressed(x, y);
}

void GameOverState::reset(){
	setFinished(false);
	setNextState("");
	//resetButton->reset();
}