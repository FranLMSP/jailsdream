#include "graphics.h"
#include "string.h"
#include "block.h"

#include <SDL2/SDL.h>
#include "iostream"
#include "stdio.h"

const int anchoVentana= 640;
const int altoVentana = 480;

/*
    The Window mode it's temporaly too, i'll
    include a configuration's file that has all
    properties of the window.

    Mode 1: 640x480 window.
    Mode 2: Fullscreen window.
    Mode 3: work in progress.
*/

const int modoVentana = 1;

/*
    The window is named "Jail's Dream" because some
    ideas in my mind, it's just a temporaly name.
*/

const char* nombreVentana="Jail's Dream";

Graphics::Graphics()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << "Error init video" << std::endl;
	}

    if (modoVentana==1)
    {
        this->_window=SDL_CreateWindow( nombreVentana, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, anchoVentana, altoVentana, SDL_WINDOW_OPENGL);
    }
    if (modoVentana==2)
    {
        this->_window=SDL_CreateWindow( nombreVentana, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, anchoVentana, altoVentana, SDL_WINDOW_FULLSCREEN);
    }

    if (this->_window==NULL)
    {
        std::cout << "Error en la ventana. Error: " << SDL_GetError() << std::endl;
    }

    this->_surface=SDL_GetWindowSurface(this->_window);
    this->_renderer = SDL_CreateRenderer(this->_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (this->_surface==NULL)
    {
        std::cout << "Error en la superficie. Error: " << SDL_GetError() << std::endl;
    }

};

void Graphics::backgroundDraw(SDL_Surface*background, SDL_Rect bg, int w, int h)
{

    SDL_FillRect(this->_surface,0,SDL_MapRGB(this->_surface->format,2,58,104));

	int aux = bg.y;
	while (bg.x < anchoVentana)
	{
		bg.y = aux;
		while (bg.y < altoVentana)
		{
			SDL_BlitSurface(background, NULL, this->_surface, &bg);
			bg.y += h;
		}
		bg.x += w;
	}
};

void Graphics::blocksDraw(Block blocks[15][20], SDL_Surface*Images[10], int h, int w)
{
    for (int j=0;j<h;j++)
    {
        for (int i=0;i<w;i++)
        {
            if (blocks[j][i].type!=0)
            {
				if (((blocks[j][i].rect.x < anchoVentana) && (blocks[j][i].rect.y < altoVentana))|| ((blocks[j][i].rect.x >=0) && (blocks[j][i].rect.y >=0)))
				{
					SDL_BlitSurface(Images[blocks[j][i].img], NULL, this->_surface, &blocks[j][i].rect);
				}
            }
        }
    }
};

void Graphics::draw(SDL_Surface* image,SDL_Rect tam,SDL_Rect rect)
{
    SDL_BlitSurface(image, &rect, this->_surface, &tam);

};

void Graphics::update()
{
    SDL_UpdateWindowSurface( this->_window );
    //SDL_Delay(1000/60);
};

Graphics::~Graphics()
{

    SDL_DestroyWindow(this->_window);
	this->_window = NULL;
};
