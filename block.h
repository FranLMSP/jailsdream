#ifndef BLOCK_H
#define BLOCK_H

#include <SDL2/SDL.h>
/*
    Types of blocks:
        0: Null.
        1: Solid.
        2: Background block.
        3: Water.
        4: Lava (or Spikes).
        5: Decorative block (same label of Solid Block).
		9: Spawnpoint
*/

struct Block
{
    int type,friction,img,hl,hr,hu,hd;
    SDL_Rect rect;
    char name;
    SDL_Surface*image;
};

#endif // BLOCK_H
