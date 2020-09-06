#include "camera.h"

char detectX, detectY;

Camera::Camera()
{

}

int Camera::detectCenter(int thing, int tam)
{
	if (thing < (tam / 2))
	{
		return 1;
	}
	else
	if (thing > (tam / 2))
	{
		return -1;
	}
	else
	{
		return 0;
	}
}

void Camera::centerAll(int thingX,int thingY, Block blocks[38][46],SDL_Rect background, char vel)
{
	detectX = this->detectCenter(thingX, 640);
	detectY = this->detectCenter(thingY, 480);

	
	thingX += vel*detectX;
	thingY += vel*detectY;
	for (int j = 0; j < 38; j++)
	{
		for (int i = 0; i < 46; i++)
		{
			blocks[j][i].rect.x += vel*detectX;
			blocks[j][i].rect.y += vel*detectY;
		}
	}

	background.x = vel / 2 * detectX;
	background.y = vel / 2 * detectY;


}

Camera::~Camera()
{

}