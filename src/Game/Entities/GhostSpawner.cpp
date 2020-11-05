#include "GhostSpawner.h"

GhostSpawner::GhostSpawner(int x, int y, int width, int height, ofImage img, EntityManager* eManager): Entity(x, y, width, height){
    this->spriteList = img;
    this->em = eManager;
    this->xPos = x;
    this->yPos = y;
}
void GhostSpawner::tick(){

    if(!fourGhostSpawned){
        for(int i = 1; i <= 4; i++) //loop 4 times and spawn a ghost 
        {
            switch(i){
                case 1:
                    {
                    Ghost* redGhost = new Ghost(this->xPos,this->yPos , 16, 16, this->spriteList, RED, this->em);
                    this->em->entities.push_back(redGhost);
                    break;
                    }
                case 2:
                    {
                    Ghost* pinkGhost = new Ghost(this->xPos,this->yPos , 16, 16, this->spriteList, PINK, this->em);
                    this->em->entities.push_back(pinkGhost);
                    break;
                    }
                case 3:
                    {
                    Ghost* cyanGhost = new Ghost(this->xPos,this->yPos , 16, 16, this->spriteList, CYAN, this->em);
                    this->em->entities.push_back(cyanGhost);
                    break;
                    }
                case 4:
                    {
                    Ghost* orangeGhost = new Ghost(this->xPos,this->yPos , 16, 16, this->spriteList, ORANGE, this->em);
                    this->em->entities.push_back(orangeGhost);
                    break;
                    }
            }
        }
        fourGhostSpawned = true;
    }
    //spawn a ghost every 150 ticks
    if(this->toSpawnList.empty()){
        this->spawnTimer = 1;
    }else if(this->spawnTimer % 150 == 0){
        Ghost* respawnedGhost = new Ghost(this->xPos, this->yPos,16,16,this->spriteList, toSpawnList[0], this->em);
        this->em->entities.push_back(respawnedGhost);
        toSpawnList.erase(toSpawnList.begin());
    }
    this->spawnTimer++;
}
void GhostSpawner::keyPressed(int key){
    if(key == 'g'){
        ofImage newImage("images/Background.png");
        //pick a random color when spawning a ghost
        switch (rand() % 4 + 1)
        {
            case 1:
            {
                Entity *newGhost = new Ghost(this->xPos, this->yPos, 16, 16, newImage, RED, this->em);
                em->entities.push_back(newGhost);
                break;
            }
            case 2:
            {
                Entity *newGhost = new Ghost(this->xPos, this->yPos, 16, 16, newImage, PINK, this->em);
                em->entities.push_back(newGhost);
                break;
            }
            case 3:
            {
                Entity *newGhost = new Ghost(this->xPos, this->yPos, 16, 16, newImage, CYAN, this->em);
                em->entities.push_back(newGhost);
                break;
            }
            case 4:
            {
                Entity *newGhost = new Ghost(this->xPos, this->yPos, 16, 16, newImage, ORANGE, this->em);
                em->entities.push_back(newGhost);
                break;
            }
            default:
            {
                Entity *newGhost = new Ghost(this->xPos, this->yPos, 16, 16, newImage, this->em);
                em->entities.push_back(newGhost);
                break;
            }
        }
    }
}
