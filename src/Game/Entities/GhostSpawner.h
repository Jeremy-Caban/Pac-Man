#include "Entity.h"
#include "Player.h"
#include "Ghost.h"
#include <vector>

class GhostSpawner: public Entity{
    private:
        bool fourGhostSpawned = false; //bool to check if the first 4 ghost have spawned
        EntityManager* em;
        ofImage spriteList;
        int xPos;
        int yPos;
        vector<color> toSpawnList;
        int spawnTimer;
    public:
        GhostSpawner(int, int, int, int, ofImage, EntityManager*);
        void addGhostToSpawn(color c){ toSpawnList.push_back(c); }
        void tick();
};
