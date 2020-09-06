#include "player.h"
#include <cstdlib>
#include <string>

SDL_Surface* walkingSprites[3];
bool played = false;
bool fplayed = false;
const float velmax=2;
const float velmin=velmax*-1;
const int velfallmax=4;
const int jumpmax=(3*32)+16;
const int jumpmin = (1 * 32) + 16;
const float velacumulator=0.15;
const float gravity=0.2;
float velder=0;
float velizq=0;
float velfall=0;
const float aceleration=4;
float jumpacum,veljump;
bool canjump,jumping,walkIReleased,walkDReleased;
bool keyreleased=true;
int diframes=9;
Sounds sound[4];


Player::Player()
{
        this->_frameCounter=diframes-1;
        this->_currentSprite=1;
        this->estaInvertida=false;
        this->state=0;

         //DEBUG
        /*this->walkingSprites[0]=SDL_LoadBMP("D:/Nautilus Game Project/bin/Debug/dt/chr/chr0.pbm");
        SDL_SetColorKey ( this->walkingSprites[0] , SDL_TRUE , SDL_MapRGB (this->walkingSprites[0] -> format , 255 , 255 , 255 ));

        this->walkingSprites[1]=SDL_LoadBMP("D:/Nautilus Game Project/bin/Debug/dt/chr/chr1.pbm");
        SDL_SetColorKey ( this->walkingSprites[1] , SDL_TRUE , SDL_MapRGB (this->walkingSprites[1] -> format , 255 , 255 , 255 ));

        this->walkingSprites[2]=SDL_LoadBMP("D:/Nautilus Game Project/bin/Debug/dt/chr/chr2.pbm");
        SDL_SetColorKey ( this->walkingSprites[2] , SDL_TRUE , SDL_MapRGB (this->walkingSprites[2] -> format , 255 , 255 , 255 ));*/


        //RELEASE
		walkingSprites[0] = NULL;
		walkingSprites[1] = NULL;
		walkingSprites[2] = NULL;
        walkingSprites[0]=SDL_LoadBMP("dt/chr/chr0.pbm");
        walkingSprites[1]=SDL_LoadBMP("dt/chr/chr1.pbm");
        walkingSprites[2]=SDL_LoadBMP("dt/chr/chr2.pbm");
		SDL_SetColorKey(walkingSprites[0],SDL_TRUE, SDL_MapRGB(walkingSprites[0]->format, 255, 255, 255));
		SDL_SetColorKey(walkingSprites[1], SDL_TRUE, SDL_MapRGB(walkingSprites[1]->format, 255, 255, 255));
		SDL_SetColorKey(walkingSprites[2], SDL_TRUE, SDL_MapRGB(walkingSprites[2]->format, 255, 255, 255));

		sound[0].loadSoundEffect("dt/s/se/C.wav");
		sound[1].loadSoundEffect("dt/s/se/J.wav");
		sound[2].loadSoundEffect("dt/s/se/W0.wav");
		sound[3].loadSoundEffect("dt/s/se/W1.wav");

        this->sprite=walkingSprites[0];

        if (this->sprite==NULL)
        {
            std::cout << "Sprite no cargado. Error: " << SDL_GetError() << std::endl;
        }
        else
        {
            std::cout << "Player's sprite loaded!" << std::endl;
        }
        this->rect.x=this->Xfisico=11*32;
        this->rect.y=this->Yfisico=64;
		

        this->tam.x=0;
        this->tam.y=0;
        this->tam.w=21;
        this->tam.h=32;
}

void Player::moverDerecha()
{
    walkDReleased=false;

    //Change sprite
    //this->animatedSprites(dif);
    if (this->estaInvertida==true)
    {
        this->estaInvertida=false;
        this->invert();
    }


    if (velder<velmax)
    {
        velder+=velacumulator;
    }
    if (this->state==5)
    {
        if (velizq>0)
        {
            velizq-=velacumulator/2;
        }
    }


}

void Player::moverIzquierda()
{
    walkIReleased=false;
    //Change sprite
    //this->animatedSprites(dif);
    if (this->estaInvertida==false)
    {
        this->estaInvertida=true;
        this->invert();
    }

    if (velizq<velmax)
    {
        velizq+=velacumulator;
    }

    if (this->state==5)
    {
        if (velder>0)
        {
            velder-=velacumulator/2;
        }
    }
}

void Player::moving(Block blocks[3][3])
{
    int d=velizq-velder;
	int sig = Xfisico - d;
	if (d == 0)
	{
		if (this->state != 5)
		{
			this->sprite = walkingSprites[0];
			
			this->_frameCounter = diframes - 1;
			this->_currentSprite = 1;
		}

	}
	else
	{
		if (this->state != 5)
		{
			this->animatedSprites(diframes);
		}
	}
	//moving left
	if (sig<this->Xfisico)
	{
		if (this->hd > blocks[1][2].hu)
		{
			if (sig + 4 < blocks[0][1].hr)
			{
				if ((blocks[0][1].type != 1) && (blocks[0][2].type != 1))
				{
					this->Xfisico = sig;

				}
				else
				{
					if (blocks[0][1].type == 1)
					{
						this->Xfisico = blocks[1][1].hl - 4;
						this->sprite = walkingSprites[0];
						velizq = 0;
						velder = 0;
					}
				}
			}
			else
			{
				this->Xfisico = sig;
			}
		}
		else
		{
			if (sig + 4 < blocks[0][1].hr)
			{
				if (blocks[0][1].type != 1)
				{
					this->Xfisico = sig;
				}
				else
				{
					if (blocks[0][1].type == 1)
					{
						this->Xfisico = blocks[1][1].hl - 4;
						this->sprite = walkingSprites[0];
						velizq = 0;
						velder = 0;
					}
				}
			}
			else
			{
				this->Xfisico = sig;
			}
		}
	}
	//moving right
	else
	if (sig>this->Xfisico)
	{
		if (this->hd > blocks[1][2].hu)
		{
			if (sig + this->tam.w - 2 > blocks[2][1].hl)
			{
				if ((blocks[2][1].type != 1) && (blocks[2][2].type != 1))
				{
					this->Xfisico = sig;
				}
				else
				{
					if (blocks[2][1].type == 1)
					{
						this->Xfisico = blocks[2][1].hl - this->tam.w + 2;
						this->sprite = walkingSprites[0];
						velizq = 0;
						velder = 0;
					}
				}
			}
			else
			{
				this->Xfisico = sig;
			}
		}
		else
		{
			if (sig + this->tam.w - 2 > blocks[2][1].hl)
			{
				if (blocks[2][1].type != 1)
				{
					this->Xfisico = sig;
				}
				else
				{
					if (blocks[2][1].type == 1)
					{
						this->Xfisico = blocks[2][1].hl - this->tam.w + 2;
						this->sprite = walkingSprites[0];
						velizq = 0;
						velder = 0;
					}
				}
			}
			else
			{
				this->Xfisico = sig;
			}
		}
	}
	else
	{
		this->Xfisico = sig;
	}


    if (walkDReleased)
    {
        if (this->state!=5)
        {
            if (velder>0)
            {
                velder-=velacumulator;
            }
        }
    }
    if (walkIReleased)
    {
        if (this->state!=5)
        {
            if (velizq>0)
            {
                velizq-=velacumulator;
            }
        }
    }


	//this->Xfisico -= d;

}

void Player::stop()
{
    if (this->state==5)
    {
        this->state=1;
        this->sprite=walkingSprites[0];
		
        this->_frameCounter=diframes-1;
        this->_currentSprite=1;
        velfall=0;
		veljump = aceleration;
		if (!fplayed)
		{
			fplayed = true;
			sound[0].playSoundEffect();
		}
    }

}

void Player::stopWalk(bool izq,bool der)
{
    if (der)
    {
        walkDReleased=true;
    }
    if (izq)
    {
        walkIReleased=true;
    }
	
    if ((walkIReleased)&&(walkDReleased))
    {

    }



}

void Player::invert()
{
    if (this->estaInvertida==false)
    {
        this->tam.x=0;
        this->tam.y=0;
    }
    else
    {
        this->tam.x=21;
        this->tam.y=0;
    }
}

void Player::update(Block blocks[3][3])
{
    this->hu=this->Yfisico+2;
    this->hd=this->Yfisico+this->tam.h;
    this->hl=this->Xfisico+4;
    this->hr=this->Xfisico+this->tam.w-3;

	if (this->hd >= blocks[1][2].hu)
	{
		if (this->hr < blocks[2][1].hl)
		{
			if (blocks[1][2].type == 1)
			{
				this->Yfisico = blocks[1][1].hu;
				this->stop();
			}
		}
		else
		if (this->hr>blocks[2][1].hl)
		{
			if ((blocks[1][2].type == 1) || (blocks[2][2].type == 1))
			{
				this->Yfisico = blocks[1][1].hu;
				this->stop();
			}
		}
	}
	
	this->rect.x = this->Xfisico;
	this->rect.y = this->Yfisico;
	




    //detect if the player is on a solid block
    if (((blocks[1][2].type!=1)&&(this->hr<blocks[2][1].hl))||((blocks[1][2].type!=1)&&(blocks[2][2].type!=1)))
    {
        if (!jumping)
        {
            std::cout << "falling" << std::endl;
            this->state=5;
            this->fall(blocks);
			fplayed = false;
        }
    }
    else
    //if ( ( (block2.type==1)&&(this->Xfisico+this->tam.w<block3.rect.x) ) || ( (this->Xfisico+this->tam.w>block3.rect.x)&&(block3.type==1)&&(block1.type!=1) ) )
    {
        std::cout << "not falling. VELDER: " << velder << " VELIZQ: " << (velizq) <<  std::endl;
        if (keyreleased)
        {
            canjump=true;
			played = false;
        }
        this->stop();
    }
    this->moving(blocks);
}

void Player::animatedSprites(int difference)
{
    this->_frameCounter++;
    if (this->_frameCounter==difference)
    {
        this->_frameCounter=0;

        if (this->_currentSprite==2)
        {
            this->sprite=walkingSprites[0];
            this->_currentSprite=3;
			sound[2].playSoundEffect();
			
        }
        else
        if (this->_currentSprite==1)
        {
            this->sprite=walkingSprites[1];
            this->_currentSprite=2;
        }
        else
        if (this->_currentSprite==3)
        {
            this->sprite=walkingSprites[2];
            this->_currentSprite=4;
        }
        else
        if (this->_currentSprite==4)
        {
            this->sprite=walkingSprites[0];
            this->_currentSprite=1;
			sound[3].playSoundEffect();
        }

    }
}

void Player::jump(Block blocks[3][3])
{
    keyreleased=false;

    if (canjump)
    {
        jumping=true;
		
    }
    if (jumping)
    {
        if (((this->hu<blocks[1][0].hd+1)&&((blocks[1][0].type==1)||((blocks[2][0].type==1)&&(hr>blocks[2][0].hl))))||(veljump<=0))
        {
            jumping=false;
			velfall = gravity;
			sound[0].playSoundEffect();
            this->fall(blocks);
			veljump = 0;

        }
        else
        {
            std::cout << "jumping" << std::endl;
			if (played==false)
			{
				sound[1].playSoundEffect();
				played = true;
			}
			this->Yfisico -= veljump;
			jumpacum += veljump;
			veljump -= gravity;
            this->state=5;
            this->sprite=walkingSprites[1];
        }
    }
}

void Player::stopJumping()
{

	canjump = false;
	jumping = false;
	keyreleased = true;

}

void Player::fall(Block blocks[3][3])
{
    std::cout << "falling" << std::endl;
    if (!jumping)
    {
        canjump=false;
    }
    this->sprite=walkingSprites[2];
    this->state=5;
    if (velfall<velfallmax)
    {
        velfall+=gravity;
    }

	this->Yfisico += velfall;

}

void Player::setSpawnPoint()
{

}

Player::~Player()
{

}
