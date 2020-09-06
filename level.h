#ifndef LEVEL_H
#define LEVEL_H

#include <SDL2/SDL.h>
#include "block.h"
#include "sounds.h"
#include <vector>

struct filetype
{
	int w, h;
	Block blocks[15][20];
	char musicname[20];
};

class Level
{
    private:

    public:
		Sounds music;
		filetype info;
		SDL_Rect BackgroundXY;
        SDL_Surface*Images[10];
		SDL_Surface*Background;

		void createLevelFile();
		void loadFile(char path[100]);
        Level();
        ~Level();
};

#endif // LEVEL_H
