#ifndef CAMERA_H
#define CAMERA_H

#include <SDL2/SDL.h>
#include "block.h"

/*
	1: thing is in the left.
	2: Thing is in the right.
	0: No one.
*/

class Camera
{
	public:
		Camera();
		~Camera();

		SDL_Rect cam = { 0,0,640,480 };
		int detectCenter(int thing,int tam);
		void centerAll(int thingX, int thingY, Block blocks[38][46], SDL_Rect background, char vel);
};

#endif // !CAMERA_H
