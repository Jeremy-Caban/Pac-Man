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

    public:
        Ghost(int, int, int, int, ofImage,EntityManager*);
        Ghost(int, int, int, int, ofImage, color,EntityManager*); //overloaded to accept a color indicator and entity manager
        int getSpeed(){ return this->speed;}
        void setSpeed(int newSpeed){ this->speed = newSpeed; }
        color getColor(){ return ghostColor; }
        void setIsVulnerable(bool newVulnerable){ this->isVulnerable = newVulnerable; }
        bool getIsVulnerable(){ return this->isVulnerable; }
        void tick();
        void render();
        void checkCollisions();
        void setDirection(DIRECTION nd){position = nd;}
};