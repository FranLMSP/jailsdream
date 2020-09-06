#include "sounds.h"
#include <stdio.h>

Sounds::Sounds()
{
	
	if (SDL_Init(SDL_INIT_AUDIO) < 0)
	{
		printf("SDL_Audio could not initialize. SDL_Audio Error: %s\n", Mix_GetError());
	}
	
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) == -1)
	{
		printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
	}
	
}

void Sounds::loadMusic(const char*path)
{
	Mix_Init(MIX_INIT_OGG);
	this->music = Mix_LoadMUS(path);
	if (music == NULL)
	{ 
		printf("Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError());
	}
}

void Sounds::loadSoundEffect(const char*path)
{
	this->sound= Mix_LoadWAV(path);
	if (this->sound == NULL) 
	{ 
		printf("Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError());
	}
}

void Sounds::playSoundEffect()
{
	Mix_Init(MIX_INIT_OGG);
	Mix_PlayChannel(-1, this->sound, 0);
}

void Sounds::playMusic()
{
	Mix_PlayMusic(this->music, -1);
}

void Sounds::pauseMusic()
{
	Mix_PauseMusic();
}

void Sounds::resumeMusic()
{
	Mix_ResumeMusic();
}

void Sounds::stopMusic()
{
	Mix_HaltMusic();
}

Sounds::~Sounds()
{
	Mix_FreeChunk(this->sound);
	this->sound = NULL;

	Mix_FreeMusic(this->music);
	this->music = NULL;

	Mix_Quit();
}
