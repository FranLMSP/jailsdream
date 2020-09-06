#include "game.h"
#include "graphics.h"
#include "player.h"
#include "input.h"
#include "camera.h"
#include "ltimer.h"
#include <time.h>
#include <ctime>
#include <stdio.h>
#include <sstream>
#include <malloc.h>

Block blocks[3][3];

Game::Game()
{
    if (SDL_Init(SDL_INIT_EVERYTHING)<0)
    {
        std::cout << "No se pudo inicializar SDL. Error: " << SDL_GetError() << std::endl;
    }
    else
    {
        std::cout << "All right!" << std::endl;
    }
    this->gameLoop();

}


void Game::gameLoop()
{
    Graphics graphics;
    Player player;
    Level level;
    Input input;
    SDL_Event event;
	Camera camera;

	level.music.loadMusic("dt/s/m/AA.wav");
	level.music.playMusic();
	//level.loadFile("AA.bin");
	level.createLevelFile();
    const int SCREEN_FPS = 60;
    const int SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;
    LTimer fpsTimer;
    LTimer capTimer;
    int countedFrames = 0;

	player.Xfisico = 16 * 32;
	player.Yfisico = 3 * 32;

    while (true)
    {

		//camera.centerAll(player.rect.x, player.rect.y, level.info.blocks,level.BackgroundXY, 4);

		blocks[0][0] = level.info.blocks[(player.hu / 32 - 1)][(player.hl / 32 - 1)];
		blocks[1][0] = level.info.blocks[(player.hu / 32 - 1)][(player.hl / 32 )];
		blocks[2][0] = level.info.blocks[(player.hu / 32 - 1)][(player.hl / 32 + 1)];
		blocks[0][1] = level.info.blocks[(player.hu / 32 )][(player.hl / 32 - 1)];
		blocks[1][1] = level.info.blocks[(player.hu / 32 )][(player.hl / 32 )];
		blocks[2][1] = level.info.blocks[(player.hu / 32 )][(player.hl / 32 + 1)];
		blocks[0][2] = level.info.blocks[(player.hu / 32 + 1)][(player.hl / 32 - 1)];
		blocks[1][2] = level.info.blocks[(player.hu / 32 + 1)][(player.hl / 32 )];
		blocks[2][2] = level.info.blocks[(player.hu / 32 + 1)][(player.hl / 32 + 1)];
		player.update(blocks);

        fpsTimer.start();
        //Start frame
        input.beginNewFrame();

        //Start timer for frame limit
        capTimer.start();

        if (SDL_PollEvent(&event))
        {
            if (event.type == SDL_KEYDOWN)
            {

                if (event.key.repeat == 0)
                {
                    input.KeyDownEvent(event);
                }
            }
            else
            if (event.type == SDL_KEYUP)
            {
                input.KeyUpEvent(event);
            }
            else
            if (event.type == SDL_QUIT)
            {
                graphics.~Graphics();
                this->~Game();
            }
        }
        if (input.wasKeyPressed(SDL_SCANCODE_ESCAPE)==true)
        {
            //Menu
            SDL_Delay(10000);
        }
        else
        if ((input.wasKeyReleased(SDL_SCANCODE_D)==true) ||
            (input.wasKeyReleased(SDL_SCANCODE_A)==true) ||
            (input.wasKeyReleased(SDL_SCANCODE_LEFT)==true) ||
            (input.wasKeyReleased(SDL_SCANCODE_RIGHT)==true))
        {

        }
        if ((input.wasKeyReleased(SDL_SCANCODE_K)==true)||(input.wasKeyReleased(SDL_SCANCODE_Z)==true))
        {
            player.stopJumping();
        }

        if ((input.isKeyHeld(SDL_SCANCODE_A)==true)||(input.isKeyHeld(SDL_SCANCODE_LEFT)==true))
        {
            player.moverIzquierda();

        }
        if ((input.isKeyHeld(SDL_SCANCODE_D)==true)||(input.isKeyHeld(SDL_SCANCODE_RIGHT)==true))
        {
            player.moverDerecha();
            /*std::cout << "Player rect.x + tam.w: " << player.rect.x+player.tam.w << std::endl;
            std::cout << "Player Block2.x: " << level.blocks[player.Yfisico/32+1][player.Xfisico/32+1].rect.x << std::endl;*/
        }
        if ((input.isKeyHeld(SDL_SCANCODE_K)==true)||(input.isKeyHeld(SDL_SCANCODE_Z)==true))
        {
            player.jump(blocks);
        }
        player.stopWalk((input.wasKeyReleased(SDL_SCANCODE_A) ||input.wasKeyReleased(SDL_SCANCODE_LEFT)),(input.wasKeyReleased(SDL_SCANCODE_D) ||input.wasKeyReleased(SDL_SCANCODE_RIGHT)));

        //Calculating correct FPS

        float avgFPS = countedFrames / ( fpsTimer.getTicks() / 1000.f );
        if( avgFPS > 2000000 )
        {
            avgFPS = 0;
        }

        //Draw everything
        graphics.backgroundDraw(level.Background,level.BackgroundXY,124,128);
        graphics.draw(player.sprite,player.rect,player.tam);
        graphics.blocksDraw(level.info.blocks,level.Images,level.info.h,level.info.w);
        graphics.update();

        //After rendering
        ++countedFrames;

        //If frame finished early
        int frameTicks = capTimer.getTicks();
        if( frameTicks < SCREEN_TICKS_PER_FRAME )
        {
            //Wait remaining time
            SDL_Delay( SCREEN_TICKS_PER_FRAME - frameTicks );
        }
    }

}

Game::~Game()
{
    SDL_Quit();
}
