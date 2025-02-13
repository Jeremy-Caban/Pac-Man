#include "ofApp.h"
#include "Images.h"


//--------------------------------------------------------------
void ofApp::setup(){
	ofSetFrameRate(30);
	ofSetWindowTitle("Java Game Box");
	//States
	menuState = new MenuState();
	gameState = new GameState();
	gameOverState = new GameOverState();
	// Initial State
	currentState = menuState;
	//--------------------(music)----------------------
	gameMusic.load("music/8_bit_flashback.mp3");
	gameOverMusic1.load("music/game_over_first_part.mp3");
	gameOverMusic2.load("music/game_over_second_part.mp3");
	gameMusic.setLoop(true);
	gameOverMusic2.setLoop(true);
	gameMusic.play();
	//-------------------------------------------------
}

//--------------------------------------------------------------
void ofApp::update(){
	if (currentState != nullptr){
		currentState->tick();
		if(currentState->hasFinished()){
			if(currentState->getNextState() == "Menu"){
				currentState = menuState;
			}else if(currentState->getNextState() == "Game"){
				//if the previous state was the menu then set it to gameState
				if(dynamic_cast<MenuState*>(currentState) != NULL){
					currentState = gameState;
				//else means we came from the GameOverState so we reset the map first
				}else{
					gameOverMusic1.stop();
					gameOverMusic2.stop();
					this->firstPartEnded = false;
					gameMusic.play();
					gameState->resetMap();
					currentState = gameState;
				}
			}
			else if (currentState->getNextState() == "GameOver")
			{	
				gameMusic.stop();
				gameOverMusic1.play();
				gameOverState->setMap(gameState->getMap());
			 	currentState = gameOverState;
			}
			
			currentState->reset();
		}
	}
	//play second part of the song after the first part is finished
	//this is because the second part loops
	if(currentState == gameOverState && gameOverMusic1.isPlaying() == false && this->firstPartEnded == false){
		gameOverMusic2.play();
		this->firstPartEnded = true;
	}	
}

//--------------------------------------------------------------
void ofApp::draw(){
	if (currentState != nullptr){
		currentState->render();
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (currentState != nullptr){
		currentState->keyPressed(key);
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
	if (currentState != nullptr)
			currentState->keyReleased(key);
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
	if (currentState != nullptr)
		currentState->mouseMoved(x, y);
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
	if (currentState != nullptr)
		currentState->mouseDragged(x, y, button);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	if (currentState != nullptr)
		currentState->mousePressed(x, y, button);
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
	if (currentState != nullptr)
		currentState->mouseReleased(x, y, button);
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){
	if (currentState != nullptr)
			currentState->mouseEntered(x, y);
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){
	if (currentState != nullptr)
		currentState->mouseExited(x, y);
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
	if (currentState != nullptr)
			currentState->windowResized(w, h);
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
	if (currentState != nullptr)
		currentState->gotMessage(msg);
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 
	if (currentState != nullptr)
		currentState->dragEvent(dragInfo);
}
