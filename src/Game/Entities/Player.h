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

    public:
        Player(int, int, int , int, EntityManager*);
        int getHealth(){return health;} //health getter
        int getScore(){return score;}
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
        int pacPosition();
        void checkCollisions();

        //-----------
        void setHealth(int newHealth){ this->health = newHealth; }
        //-----------
};