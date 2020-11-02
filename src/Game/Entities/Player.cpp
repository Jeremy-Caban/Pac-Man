#include "Player.h"
#include "EntityManager.h"
#include "Dot.h"
#include "BigDot.h"
#include "Ghost.h"
#include "GameOverState.h"
#include <ctime>
#include <cstdlib>

Player::Player(int x, int y, int width, int height, EntityManager *em) : Entity(x, y, width, height)
{
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
    for (int i = 0; i < 3; i++)
    {
        temp.cropFrom(sprite, i * 16, 48, 16, 16);
        downAnimframes.push_back(temp);
    }
    for (int i = 0; i < 3; i++)
    {
        temp.cropFrom(sprite, i * 16, 32, 16, 16);
        upAnimframes.push_back(temp);
    }
    for (int i = 0; i < 3; i++)
    {
        temp.cropFrom(sprite, i * 16, 16, 16, 16);
        leftAnimframes.push_back(temp);
    }
    for (int i = 0; i < 3; i++)
    {
        temp.cropFrom(sprite, i * 16, 0, 16, 16);
        rightAnimframes.push_back(temp);
    }
    walkDown = new Animation(1, downAnimframes);
    walkUp = new Animation(1, upAnimframes);
    walkLeft = new Animation(1, leftAnimframes);
    walkRight = new Animation(1, rightAnimframes);

    this->em = em;
    //save coordinates to respawn when you die
    this->startingXPos = x;
    this->startingYPos = y;
}
void Player::tick()
{
    canMove = true;
    checkCollisions();
    //after 500 ticks the ghosts will start chasing pacman
    if(this->ticks >= 500 && this->ticks < 1000){
        int a = rand() % 5;
        if (a == 0)
        {
            chaser();
        }
    }else if( this->ticks >= 1000){
        this->ticks = 0;
    }
    if (canMove)
    {
        if (facing == UP)
        {
            y -= speed;
            walkUp->tick();
        }
        else if (facing == DOWN)
        {
            y += speed;
            walkDown->tick();
        }
        else if (facing == LEFT)
        {
            x -= speed;
            walkLeft->tick();
        }
        else if (facing == RIGHT)
        {
            x += speed;
            walkRight->tick();
        }
    }
    this->ticks++;

    //note: "== true" and "== false" is used to improve readability and is not entirely necessary for it to function equally

    //whilst powered up, start the powered up timer
    if(this->getIsPoweredUp() == true && this->poweredUpTimer < 300){
        this->poweredUpTimer++;
    }else{
    //reset timer and remove power up when time is exceeded
        this->poweredUpTimer = 0;
        this->setIsPoweredUp(false);
    }
    //while powered up, all ghost should become vulnerable
    if(this->getIsPoweredUp() == true){
        for(Entity* entity: em->entities)
        {
            if(dynamic_cast<Ghost*>(entity)){
                dynamic_cast<Ghost*>(entity)->setIsVulnerable(true);
                dynamic_cast<Ghost*>(entity)->setSpeed(2);
            }
        }
    }else if(this->getIsPoweredUp() == false){
        for(Entity* entity: em->entities)
        {
            if(dynamic_cast<Ghost*>(entity)){
                dynamic_cast<Ghost*>(entity)->setIsVulnerable(false);
                dynamic_cast<Ghost*>(entity)->setSpeed(4);
            }
        }
    }
}

void Player::render()
{

    ofSetColor(256, 256, 256);
    //Display lives
    ofDrawBitmapString("Lives: " + to_string(health), 80, 50);
    //Display score;
    ofDrawBitmapString("Score: " + to_string(score), 80, 70);
    //Display a message once the ghost start chasing you
    if(this->ticks >= 500){
        ofDrawBitmapString("The Ghosts are more inclined to chase you now...", 340, 30);
    }
    if (facing == UP)
    {
        walkUp->getCurrentFrame().draw(x, y, width, height);
    }
    else if (facing == DOWN)
    {
        walkDown->getCurrentFrame().draw(x, y, width, height);
    }
    else if (facing == LEFT)
    {
        walkLeft->getCurrentFrame().draw(x, y, width, height);
    }
    else if (facing == RIGHT)
    {
        walkRight->getCurrentFrame().draw(x, y, width, height);
    }

}
void Player::keyPressed(int key)
{
    switch (key)
    {
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
    //Increase pacmans' health if it aint maxed out
    case 'm':
        if (this->health < this->MAXhealth)
        {
            this->health++;
        }
        break;

    case 'g':
        ofImage newImage("images/Background.png");
        srand(time(0));
        //pick a random color when spawning a ghost
        switch (rand() % 4 + 1)
        {
            case 1:
            {
                Entity *newGhost = new Ghost(504, 368, 16, 16, newImage, RED, this->em);
                em->entities.push_back(newGhost);
                break;
            }
            case 2:
            {
                Entity *newGhost = new Ghost(504, 368, 16, 16, newImage, PINK, this->em);
                em->entities.push_back(newGhost);
                break;
            }
            case 3:
            {
                Entity *newGhost = new Ghost(504, 368, 16, 16, newImage, CYAN, this->em);
                em->entities.push_back(newGhost);
                break;
            }
            case 4:
            {
                Entity *newGhost = new Ghost(504, 368, 16, 16, newImage, ORANGE, this->em);
                em->entities.push_back(newGhost);
                break;
            }
            default:
            {
                Entity *newGhost = new Ghost(504, 368, 16, 16, newImage, this->em);
                em->entities.push_back(newGhost);
                break;
            }
        }
        break;
    }
}

void Player::die()
{
    //reduce health by one and teleport to the start
    this->health = this->health - 1;
    this->x = this->startingXPos;
    this->y = this->startingYPos;
}

void Player::keyReleased(int key)
{
    if (key == 'w' || key == 's' || key == 'a' || key == 'd')
    {
        walking = false;
    }
}
void Player::mousePressed(int x, int y, int button)
{
}

void Player::setFacing(FACING facing)
{
    this->facing = facing;
}

void Player::chaser()
{
    //makes ghost chase pacman based on where the player is located
    srand(time(0));
    for (Entity *entity : em->entities)
    {
        Ghost *c1 = dynamic_cast<Ghost *>(entity);
        //will only chase pacman after getting out of the box to prevent it from getting stuck
        if (c1 != nullptr && c1->getIsOutOfBox() ==  true){
            unsigned int s = rand() % 2;
            if (s == 0 && this->getY() > c1->getY()){
                c1->setDirection(D);
            }else if(s == 0 && this->getY() < c1->getY()){
                c1->setDirection(U);
            }else if(s == 1 && this->getX() > c1->getX()){
                c1->setDirection(R);
            }else{
                c1->setDirection(L);
            }
        }
    }
}
void Player::checkCollisions()
{
    for (Block *block : em->blocks)
    {
        switch (facing)
        {
        case UP:
            if (this->getBounds(x, y - speed).intersects(block->getBounds()))
            {
                canMove = false;
            }
            break;
        case DOWN:
            if (this->getBounds(x, y + speed).intersects(block->getBounds()))
            {
                canMove = false;
            }
            break;
        case LEFT:
            if (this->getBounds(x - speed, y).intersects(block->getBounds()))
            {
                canMove = false;
            }
            break;
        case RIGHT:
            if (this->getBounds(x + speed, y).intersects(block->getBounds()))
            {
                canMove = false;
            }
            break;
        }
    }
    for (Entity *entity : em->entities)
    {
        if (collides(entity))
        {
            if (dynamic_cast<Dot*>(entity) || dynamic_cast<BigDot*>(entity))
            {
                entity->remove = true;
                //add to the score when player eats a dot
                if (dynamic_cast<Dot *>(entity))
                {
                    this->score += 5;
                }
                else if (dynamic_cast<BigDot*>(entity))
                {
                    this->score += 10;
                    this->setIsPoweredUp(true);
                }
                break; //this should prevent a segmentation fault that occurs when eating more than one entity at the same time
            }
            else if (dynamic_cast<Ghost*>(entity) && this->getIsPoweredUp() == false)
            {
                die();
                break; //this should prevent a segmentation fault that occurs when eating more than one entity at the same time
            }
            else if (dynamic_cast<Ghost*>(entity) && this->getIsPoweredUp() == true){
                //save the ghosts color before removing
                for(Entity* e: this->em->entities){
                    if(dynamic_cast<GhostSpawner*>(e)){
                        dynamic_cast<GhostSpawner*>(e)->addGhostToSpawn(dynamic_cast<Ghost*>(entity)->getColor());
                    }
                }
                entity->remove = true;
                break; //this should prevent a segmentation fault that occurs when eating more than one entity at the same time
            }
        }
    }
}