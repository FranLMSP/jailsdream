#ifndef PLAYER_H
#define PLAYER_H

#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "block.h"
#include "sounds.h"

/*
    State 1: Character not moving in the floor.
    State 2: Character moving to the left.
    State 3: Character moving to the right.
    State 4: Jumping.
    State 5: Falling.
    State 6: Invulnerable.

    hitbox1:left
    hitbox2:right
    hitbox3:up
    hitbox4:down
*/

class Player
{
    private:
        int _frameCounter,_currentSprite,state;

        void animatedSprites(int difference);
        bool estaInvertida;


    public:
        SDL_Surface* sprite=NULL;
        int hu,hd,hl,hr;
        SDL_Rect rect;
        SDL_Rect tam;
        void moverDerecha();
        void moverIzquierda();
        void moving(Block blocks[3][3]);
        void jump(Block blocks[3][3]);
        void fall(Block blocks[3][3]);
        void stop();
        void stopWalk(bool izq,bool der);
        void stopJumping();
        void invert();
        void update(Block blocks[3][3]);

		void setSpawnPoint();

        int Xfisico,Yfisico;
        Player();
        ~Player();
};

#endif // PLAYER_H
