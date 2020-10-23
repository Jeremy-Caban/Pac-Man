#include "Player.h"
#include "EntityManager.h"
#include "Dot.h"
#include "BigDot.h"
#include "Ghost.h"
#include "GameOverState.h"
#include <ctime>
#include <cstdlib>

Player::Player(int x, int y, int width, int height, EntityManager* em) : Entity(x, y, width, height){
    sprite.load("images/pacman.png");
    down.cropFrom(sprite, 0, 48, 16, 16);
    up.cropFrom(sprite, 0, 32, 16, 16);
    left.cropFrom(sprite, 0, 16, 16, 16);
    right.cropFrom(sprite, 0, 0, 16, 16);
    
    vector<ofImage> downAnimframes;
    vector<ofImage> upAnimframes;
    vector<ofImage> leftAnimframes;
    vector<ofImage> rightAnimframes;
    ofImage temp;
    for(int i=0; i<3; i++){
        temp.cropFrom(sprite, i*16, 48, 16, 16);
        downAnimframes.push_back(temp);
    }
    for(int i=0; i<3; i++){
        temp.cropFrom(sprite, i*16, 32, 16, 16);
        upAnimframes.push_back(temp);
    }
    for(int i=0; i<3; i++){
        temp.cropFrom(sprite, i*16, 16, 16, 16);
        leftAnimframes.push_back(temp);
    }
    for(int i=0; i<3; i++){
        temp.cropFrom(sprite, i*16, 0, 16, 16);
        rightAnimframes.push_back(temp);
    }
    walkDown = new Animation(1,downAnimframes);
    walkUp = new Animation(1,upAnimframes);
    walkLeft = new Animation(1,leftAnimframes);
    walkRight = new Animation(1,rightAnimframes);

    this->em = em;
    
}
void Player::tick(){
    canMove = true;
    checkCollisions();
    if(canMove){
        if(facing == UP){
            y-= speed;
            walkUp->tick();
        }else if(facing == DOWN){
            y+=speed;
            walkDown->tick();
        }else if(facing == LEFT){
            x-=speed;
            walkLeft->tick();
        }else if(facing == RIGHT){
            x+=speed;
            walkRight->tick();
        }
    }
}

void Player::render(){

    ofSetColor(256,256,256);
	ofDrawBitmapString("Lives: " + to_string(health), 80, 50);
    // ofDrawRectangle(getBounds());
    if(facing == UP){
        walkUp->getCurrentFrame().draw(x, y, width, height);
        
    }else if(facing == DOWN){
        walkDown->getCurrentFrame().draw(x, y, width, height);
    }else if(facing == LEFT){
        walkLeft->getCurrentFrame().draw(x, y, width, height);
    }else if(facing == RIGHT){
        walkRight->getCurrentFrame().draw(x, y, width, height);
    }

    ofDrawBitmapString("Score: " + to_string(score), 80, 70);    
}
//Pac health
int MAXhealth = 3;
int health = MAXhealth;
void Player::keyPressed(int key){
    switch(key){
        case 'w':
            setFacing(UP);
            break;
        case 's':
            setFacing(DOWN);
            break;
        case 'a':
            setFacing(LEFT);
            break;
        case 'd':
            setFacing(RIGHT);
            break;
         //Reduce pac health   
        case 'n':
            if (this->health > 0)
            {
                this->health--;
            }
            break;
        //Increase pac health
        case 'm':
            if (this->health < MAXhealth)
            {
                this->health++;
            }
            break;
            
        case 'g':
            ofImage  newImage("images/Background.png");
            srand(time(0));
            //pink a random color when spawning a ghost
            switch(rand() % 4 + 1){
                case 1:
                    {
                    Entity* newGhost = new Ghost(504, 368, 16, 16, newImage,RED);
                    em->entities.push_back(newGhost);
                    break;
                    }
                case 2:
                    {
                    Entity* newGhost = new Ghost(504, 368, 16, 16, newImage, PINK);
                    em->entities.push_back(newGhost);
                    break;
                    }
                case 3:
                    {
                    Entity* newGhost = new Ghost(504, 368, 16, 16, newImage, CYAN);
                    em->entities.push_back(newGhost);
                    break;
                    }
                case 4:
                    {
                    Entity* newGhost = new Ghost(504, 368, 16, 16, newImage, ORANGE);
                    em->entities.push_back(newGhost);
                    break;
                    }
                default:
                    {
                    Entity* newGhost = new Ghost(504, 368, 16, 16, newImage);
                    em->entities.push_back(newGhost);
                    break;
                    }
            }
            break;
    }
}

void Player::die(){

    this->health = this->health - 1;
    this->x = 312;
    this->y = 640;
}

void Player::keyReleased(int key){
    if(key == 'w' || key =='s' || key == 'a' || key == 'd'){
        walking = false;
    }
}
void Player::mousePressed(int x, int y, int button){

}

void Player::setFacing(FACING facing){
    this->facing = facing;
}

void Player::checkCollisions(){
    for(Block* block: em->blocks){
        switch(facing){
            case UP:
                if(this->getBounds(x, y-speed).intersects(block->getBounds())){
                    canMove = false;
                }
                break;
            case DOWN:
                if(this->getBounds(x, y+speed).intersects(block->getBounds())){
                    canMove = false;
                }
                break;
            case LEFT:
                if(this->getBounds(x-speed, y).intersects(block->getBounds())){
                    canMove = false;
                }
                break;
            case RIGHT:
                if(this->getBounds(x+speed, y).intersects(block->getBounds())){
                    canMove = false;
                }
                break;
        }
    }
    for(Entity* entity:em->entities){
        if(collides(entity)){
            if(dynamic_cast<Dot*>(entity) || dynamic_cast<BigDot*>(entity)){
                entity->remove = true;
                //add to the score when player eats a dot
                if(dynamic_cast<Dot*>(entity)){
                    this->score += 5;
                }else if(dynamic_cast<BigDot*>(entity)){
                    this->score += 10;
                }
            }

            if(dynamic_cast<Ghost*>(entity)){
                die();
            }
        }
    }
    
}