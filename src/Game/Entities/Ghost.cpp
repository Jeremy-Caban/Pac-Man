#include "Ghost.h"

Ghost::Ghost(int x, int y, int width, int height, ofImage spriteSheet): Entity(x, y, width, height){
    sprite.cropFrom(spriteSheet,456,64,16,16);
}
Ghost::Ghost(int x, int y, int width, int height, ofImage spriteSheet, color color): Entity(x, y, width, height){
    switch(color){
        //crop a different colored ghost depending on the color indicator (1-4)
        case RED:
            sprite.cropFrom(spriteSheet,456,64,16,16);
            break;
        case PINK:
            sprite.cropFrom(spriteSheet,456,80,16,16);
            break;
        case CYAN:
            sprite.cropFrom(spriteSheet,456,96,16,16);
            break;
        case ORANGE:
            sprite.cropFrom(spriteSheet,456,112,16,16);
            break;
        default: // red will be the default color
            sprite.cropFrom(spriteSheet,456,64,16,16);
            break;
    }
}