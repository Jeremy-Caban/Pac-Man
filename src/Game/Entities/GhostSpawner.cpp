#include "GhostSpawner.h"

GhostSpawner::GhostSpawner(int x, int y, int width, int height, ofImage img, EntityManager* eManager): Entity(x, y, width, height){
    this->spriteList = img;
    this->em = eManager;
}
void GhostSpawner::tick(){

    if(!fourGhostSpawned){
        for(int i = 1; i <= 4; i++) //loop 4 times and spawn a ghost 
        {
            switch(i){
                case 1:
                    {
                    Ghost* redGhost = new Ghost(504, 368 - (16 * (i-1)), 16, 16, this->spriteList, RED);
                    this->em->entities.push_back(redGhost);
                    break;
                    }
                case 2:
                    {
                    Ghost* pinkGhost = new Ghost(504, 368 - (16 * (i-1)), 16, 16, this->spriteList, PINK);
                    this->em->entities.push_back(pinkGhost);
                    break;
                    }
                case 3:
                    {
                    Ghost* cyanGhost = new Ghost(504, 368 - (16 * (i-1)), 16, 16, this->spriteList, CYAN);
                    this->em->entities.push_back(cyanGhost);
                    break;
                    }
                case 4:
                    {
                    Ghost* orangeGhost = new Ghost(504, 368 - (16 * (i-1)), 16, 16, this->spriteList, ORANGE);
                    this->em->entities.push_back(orangeGhost);
                    break;
                    }
            }
        }
        fourGhostSpawned = true;
    }
}

//void GhostSpawner::render(){}
//void GhostSpawner::reset(){}