#include "Player.h"
#pragma once
class Map{
    public:
      Map(EntityManager*);
      // int health = 3;
      void addBlock(Block*);
      void addEntity(Entity*);
      void setPlayer(Player*);
      void tick();
      void render();
      void keyPressed(int key);
		  void mousePressed(int x, int y, int button);
		  void keyReleased(int key);

    private:
      EntityManager *entityManager;
      Player *player;
      bool gameStop = false;
};