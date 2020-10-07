#pragma once
#include <vector>
#include <algorithm>

#include "GameObject.h"
#include "AniManager.h"
#include "Bullet.h"

const int FALCONSPEED = 10;
const int BULLETCD = 10;

class Falcon:public GameObject
{
public:
	//Falcon();
	Falcon(const char* TextureSheet, int x, int y):GameObject(TextureSheet,x,y)
	{
		FalconSpeed = FALCONSPEED;
		FalconBulletCD = BULLETCD;
		FalconBulletInterval = 0;
	}
	//~Falcon();

	void Update();
	//void Render();
	//void Destroy();
	void BulletUpdate(GameObject* ComFighter, int& PlayerScore);
	int getBulletCD()
	{
		return FalconBulletCD;
	}

	int getFalconSpeed()
	{
		return FalconSpeed;
	}

	std::vector<Bullet*> PlayerBulletVec;

	int FalconBulletInterval;
private:
	int FalconSpeed;
	int FalconBulletCD;
	bool isActive;
};
