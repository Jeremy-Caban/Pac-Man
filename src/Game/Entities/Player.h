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
        int health = 3;
        int score = 0; //set score to 0
        bool canMove;
        int speed = 4;
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
        int getHealth();
        int getScore();
        void tick();
        void render();
        void keyPressed(int);
        void keyReleased(int);
        void damage(Entity* damageSource);
        void die();
        void mousePressed(int, int, int);
        void reset();
        void setFacing(FACING facing);
        void checkCollisions();
};