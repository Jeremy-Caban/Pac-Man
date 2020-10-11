#include "MenuState.h"

MenuState::MenuState() {
	startButton = new Button(ofGetWidth()/2, ofGetHeight()/2, 900, 350, "Start");
	
}
void MenuState::tick() {
	startButton->tick();
	if(startButton->wasPressed()){
		setNextState("Game");
		setFinished(true);

	}
}
void MenuState::render() {
	
	//ofSetBackgroundColor(0, 0, 0);
	// startButton->render();
	 ofImage GameBackground("images/ChasingPac.png");
	 GameBackground.draw(0, 0,ofGetWidth(),ofGetHeight());
	 ofImage startButton("images/Start.jpg");
	 startButton.draw(830, 340, ofGetWidth() / 6, ofGetHeight() / 6);
}

void MenuState::keyPressed(int key){
	
}

void MenuState::mousePressed(int x, int y, int button){
	startButton->mousePressed(x, y);
}

void MenuState::reset(){
	setFinished(false);
	setNextState("");
	startButton->reset();
}