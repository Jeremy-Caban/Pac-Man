#include "Ghost.h"
#include "Player.h"

Ghost::Ghost(int x, int y, int width, int height, ofImage spriteSheet,EntityManager* em): Entity(x, y, width, height){
    sprite.cropFrom(spriteSheet,456,64,16,16);
    this->em = em;
}
Ghost::Ghost(int x, int y, int width, int height, ofImage spriteSheet, color color,EntityManager* em): Entity(x, y, width, height){
    switch(color){
        //crop a different colored ghost depending on the color indicator (1-4)
        case RED:
            sprite.cropFrom(spriteSheet,456,64,16,16);
            this->em = em;
            break;
        case PINK:
            sprite.cropFrom(spriteSheet,456,80,16,16);
            this->em = em;
            break;
        case CYAN:
            sprite.cropFrom(spriteSheet,456,96,16,16);
            this->em = em;
            break;
        case ORANGE:
            sprite.cropFrom(spriteSheet,456,112,16,16);
            this->em = em;
            break;
        default: // red will be the default color
            sprite.cropFrom(spriteSheet,456,64,16,16);
            this->em = em;
            break;
    }
}
void Ghost::tick(){
    canMove = true;
    checkCollisions();
    if(canMove){
        if(position == U){
            y-= speed;
        }else if(position == D){
            y+=speed;
        }else if(position == L){
            x-=speed;
        }else if(position == R){
            x+=speed;
        }
    }
}
// int Ghost::pacPosition()
// {
//     srand(time(0));
//     for (Entity *entity : em->entities)
//     {
//         Ghost *c1 = dynamic_cast<Ghost *>(entity);
//         Player *c2 = dynamic_cast<Player *>(entity);
//         if (c2 != nullptr)
//         {
//            return ;
//            break;
//         }
//     }
// }
void Ghost::checkCollisions(){
    srand(time(0));
    int p = 9;
    for(Block* block:em->blocks){
        switch(position){
            case U:
                if(this->getBounds(x, y-speed).intersects(block->getBounds())){
                    canMove = false;
                    int r = rand() % 2;
                    if (r == 0)
                    {
                        setDirection(L);
                    }
                    else
                    {
                        setDirection(R);
                    }
                    
                }
                break;
            case D:
                if(this->getBounds(x, y+speed).intersects(block->getBounds())){
                    canMove = false;
                    int r = rand() % 2;
                     if (r == 0)
                    {
                        setDirection(L);
                    }
                    else
                    {
                        setDirection(R);
                    }
                }
                break;
            case L:
                if(this->getBounds(x-speed, y).intersects(block->getBounds())){
                    canMove = false;
                    int r = rand() % 2;
                    if (r == 0)
                    {
                        setDirection(D);
                    }
                    else
                    {
                        setDirection(U);
                    }
                }
                break;
            case R:
                if(this->getBounds(x+speed, y).intersects(block->getBounds())){
                    canMove = false;
                    int r = rand() % 2;
                     if (r == 0)
                    {
                        setDirection(U);
                    }
                    else
                    {
                        setDirection(D);
                    }
                }
                break;
        }
    }
}