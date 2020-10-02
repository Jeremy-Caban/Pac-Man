#include "Ghost.h"

Ghost::Ghost(int x, int y, int width, int height, ofImage spriteSheet): Entity(x, y, width, height){
    sprite.cropFrom(spriteSheet,456,64,16,16);
}