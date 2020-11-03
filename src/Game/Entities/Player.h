#pragma once
#include "Animation.h"

#include "EntityManager.h"

enum FACING {
    UP,
    DOWN,
    LEFT,
    RIGHT
};

class Player: public Entity{

    private:
        //Pac health
        int MAXhealth = 3;
        int health = 3;//Pac Health
        int score = 0; //set score to 0
        bool canMove;
        int speed = 8;
        bool walking = false;
        FACING facing = DOWN;
        ofImage up, down, left, right;
        Animation *walkUp;
        Animation *walkDown;
        Animation *walkLeft;
        Animation *walkRight;
        EntityManager* em;
        int startingXPos;
        int startingYPos;
        bool isPoweredUp = false;
        int poweredUpTimer;
    public:
        Player(int, int, int , int, EntityManager*);
        int getHealth(){return health;} //health getter
        void setHealth(int newHealth){ this->health = newHealth; }
        int getScore(){return score;}
        //-----------------------------------------------------
        bool getIsPoweredUp(){ return isPoweredUp; }
        void setIsPoweredUp(bool nP){ this->isPoweredUp = nP; }
        //-----------------------------------------------------
        void tick();
        void render();
        void keyPressed(int);
        void keyReleased(int);
        void damage(Entity* damageSource);
        void die();
        void mousePressed(int, int, int);
        void reset();
        void setFacing(FACING facing);
        void chaser();
        void runAway();
        void checkCollisions();
};