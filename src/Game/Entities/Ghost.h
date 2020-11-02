#pragma once
#include "Entity.h"
#include "EntityManager.h"
#include <cstdlib>
#include <ctime>
#include "Animation.h"

enum DIRECTION {
    U,
    D,
    L,
    R
};

enum color{
        RED = 1, 
        PINK = 2,
        CYAN = 3,
        ORANGE = 4,
};
class Ghost: public Entity{
    private:
        int speed = 4;
        bool canMove;
        bool isVulnerable = false;
        ofImage ghostPic;
        color ghostColor;
        EntityManager *em;
        DIRECTION position = U;
        Animation* vulnerableState;
        vector<ofImage> frames;
        ofImage firstFrame;
        ofImage secondFrame;
        bool isOutOfBox = false;

    public:
        Ghost(int, int, int, int, ofImage,EntityManager*);
        Ghost(int, int, int, int, ofImage, color,EntityManager*); //overloaded to accept a color indicator and entity manager
        //getters
        int getSpeed(){ return this->speed; }
        color getColor(){ return ghostColor; }
        bool getIsVulnerable(){ return this->isVulnerable; }
        bool getIsOutOfBox(){ return isOutOfBox; }
        //setters
        void setSpeed(int newSpeed){ this->speed = newSpeed; }
        void setIsVulnerable(bool newVulnerable){ this->isVulnerable = newVulnerable; }
        void setDirection(DIRECTION nd){position = nd;}
        
        void tick();
        void render();
        void checkCollisions();
        
};