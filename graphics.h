#ifndef GRAPHICS_H
#define GRAPHICS_H
#include "level.h"
#include <SDL2/SDL.h>

class Graphics
{
    private:
        int alto,ancho,cant;
        SDL_Window* _window = NULL;
        SDL_Surface* _surface=NULL;
        SDL_Renderer*_renderer=NULL;
        SDL_Texture *_bitmapTex = NULL;


    public:
        void backgroundDraw(SDL_Surface*background, SDL_Rect bg, int w, int h);
        void blocksDraw(Block blocks[15][20], SDL_Surface*Images[10],  int h, int w);
        void draw(SDL_Surface* image,SDL_Rect tam,SDL_Rect rect);
        void update();
        Graphics();
        ~Graphics();

};

#endif // GRAPHICS_H
