#pragma once
#include "ofMain.h" 
#include "Map.h"
#include "Dot.h"
#include "BigDot.h"
#include "Ghost.h"
#include "GhostSpawner.h"
class MapBuilder {
    public:
        MapBuilder();
	    Map* createMap(ofImage);

	private:
        vector<ofImage> bound;
        int pixelMultiplier;
        ofColor boundBlock;
        ofColor pacman;
        ofColor ghostC;
	    ofColor dotC;
	    ofColor bigDotC;
        ofImage pacmanSpriteSheet;
        ofImage tempBound;
        ofImage getSprite(ofImage, int, int);
        EntityManager* entityManager;
};