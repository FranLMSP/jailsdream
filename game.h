#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>

struct Player;
struct Level;
struct Block;



class Game
{
    private:
        void gameLoop();
    public:

        Game();
        ~Game();

};

#endif // GAME_H
