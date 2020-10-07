#include "Bullet.h"
#include <math.h>

#include <iostream>

const int BULLETWIDTH = 5;
const int BULLETHEIGHT = 5;
const int WINDOWWIDTH = 800;
const int WINDOWHEIGHT = 600;

Bullet::Bullet(std::string shooter,int x,int y)
{
	InitX = x;
	InitY = y;
	DestRect.x = x;
	DestRect.y = y;
	DestRect.w = BULLETWIDTH;
	DestRect.h = BULLETHEIGHT;
	isActive = true;
	//std::cout << "SHOOT!" << std::endl;

	if(shooter=="player")
	{
		TargetX = x;
		TargetY = -10;
		SpeedX = 0;
		SpeedY = -BULLETSPEED;
	}
	else if(shooter=="fighter")
	{
		TargetX = x;
		TargetY = WINDOWHEIGHT+10;
		SpeedX = 0;
		SpeedY = BULLETSPEED;
	}

	//Distance = sqrt(pow((TargetX - InitX), 2) + pow((TargetY - InitY), 2));
}

Bullet::Bullet(std::string shooter,int x, int y, SDL_Rect TargetRect)
{
	InitX = x;
	InitY = y;
	DestRect.x = x;
	DestRect.y = y;
	DestRect.w = BULLETWIDTH;
	DestRect.h = BULLETHEIGHT;
	isActive = true;
	if (shooter == "player")
	{
		TargetX = x;
		TargetY = -100;
	}
	else if (shooter == "fighter")
	{
		TargetX = TargetRect.x;
		TargetY = TargetRect.y;
	}

	Distance = sqrt(pow((TargetX - InitX), 2) + pow((TargetY - InitY), 2));
	SpeedX = (BULLETSPEED / Distance) * (TargetX - InitX);
	SpeedY = (BULLETSPEED / Distance) * (TargetY - InitY);
}

void Bullet::PlayerUpdate()
{
	DestRect.x += SpeedX;
	DestRect.y += SpeedY;
	if(DestRect.y<0||DestRect.y>WINDOWHEIGHT||DestRect.x<0||DestRect.x>WINDOWWIDTH)
	{
		isActive = false;
	}
}

void Bullet::ComUpdate()
{
	DestRect.x += SpeedX;
	DestRect.y += SpeedY;
	if (DestRect.y<0 || DestRect.y>WINDOWHEIGHT || DestRect.x<0 || DestRect.x>WINDOWWIDTH)
	{
		isActive = false;
	}
}

bool Bullet::isCollidingWith(const GameObject& other)
{	
	int otherXMin = other.getDestRect().x;
	int ourXMin = DestRect.x;

	int otherXMax = other.getDestRect().x + other.getDestRect().w;
	int ourXMax = DestRect.x + DestRect.w;

	bool overlapX = ourXMin < otherXMax&& ourXMax > otherXMin;

	int otherYMin = other.getDestRect().y;
	int ourYMin = DestRect.y;

	int otherYMax = other.getDestRect().y + other.getDestRect().h;
	int ourYMax = DestRect.y + DestRect.h;

	bool overlapY = ourYMin < otherYMax&& ourYMax > otherYMin;

	if (overlapX == true && overlapY == true)
	{
		return true;
	}
	else
	{
		return false;
	}
}