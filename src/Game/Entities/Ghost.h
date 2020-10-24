#pragma once
#include "Entity.h"
#include "EntityManager.h"

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
        color ghostColor;
        int speed = 4;
        bool canMove;
        EntityManager *em;
        DIRECTION position = U;
    public:
        Ghost(int, int, int, int, ofImage);
        Ghost(int, int, int, int, ofImage, color); //overloaded to accept a color indicator and entity manager
        Ghost(int, int, int, int, ofImage,EntityManager*);
        int getSpeed(){ return this->speed;}
        void setSpeed(int newSpeed){ this->speed = newSpeed;}
        color getColor(){ return ghostColor; }
        
        void tick();
        void checkCollisions();
};