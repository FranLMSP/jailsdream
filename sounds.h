#ifndef SOUNDS_H
#define SOUNDS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>
#include <string>

class Sounds
{
	private:

	public:
		//The music that will be played
		Mix_Music *music = NULL;
		//The sound effects that will be used
		Mix_Chunk *sound = NULL;

		void loadMusic(const char*path);
		void loadSoundEffect(const char*path);

		void playSoundEffect();

		void playMusic();
		void pauseMusic();
		void resumeMusic();
		void stopMusic();


		Sounds();
		~Sounds();

};

#endif // LEVEL_H
