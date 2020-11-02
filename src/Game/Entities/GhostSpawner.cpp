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
