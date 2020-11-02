#include "Ghost.h"
#include "Player.h"

Ghost::Ghost(int x, int y, int width, int height, ofImage spriteSheet,EntityManager* em): Entity(x, y, width, height){
    this->ghostPic.cropFrom(spriteSheet,456,64,16,16);
    this->em = em;
    //create vulnerable animation
    firstFrame.cropFrom(spriteSheet,584,64,16,16);
    secondFrame.cropFrom(spriteSheet,616,64,16,16);
    this->frames.push_back(firstFrame);
    this->frames.push_back(secondFrame);
    vulnerableState = new Animation(3, frames);
}
Ghost::Ghost(int x, int y, int width, int height, ofImage spriteSheet, color color,EntityManager* em): Entity(x, y, width, height){
    switch(color){
        //crop a different colored ghost depending on the color indicator (1-4)
        case RED:
            this->ghostPic.cropFrom(spriteSheet,456,64,16,16);
            this->em = em;
            break;
        case PINK:
            this->ghostPic.cropFrom(spriteSheet,456,80,16,16);
            this->em = em;
            break;
        case CYAN:
            this->ghostPic.cropFrom(spriteSheet,456,96,16,16);
            this->em = em;
            break;
        case ORANGE:
            this->ghostPic.cropFrom(spriteSheet,456,112,16,16);
            this->em = em;
            break;
        default: // red will be the default color
            this->ghostPic.cropFrom(spriteSheet,456,64,16,16);
            this->em = em;
            break;
    }
    //create vulnerable animation
    firstFrame.cropFrom(spriteSheet,584,64,16,16);
    secondFrame.cropFrom(spriteSheet,616,64,16,16);
    this->frames.push_back(firstFrame);
    this->frames.push_back(secondFrame);
    vulnerableState = new Animation(3, frames);
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
void Ghost::render(){
    if(this->getIsVulnerable() == false){ //draw the ghost while not vulnerable
        this->ghostPic.draw(x,y,width,height);
    }else if(this->getIsVulnerable() == true){ //else will draw vulnerable animation 
        this->vulnerableState->getCurrentFrame().draw(x,y,width,height);
        vulnerableState->tick();
    }
   
}
void Ghost::checkCollisions(){
    for(Block* block:em->blocks){
        switch(position){
            case U:
                if(this->getBounds(x, y-speed).intersects(block->getBounds())){
                    canMove = false;
                    unsigned int r = rand() % 2;
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
                    unsigned int r = rand() % 2;
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
                    unsigned int r = rand() % 2;
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
                    unsigned int r = rand() % 2;
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