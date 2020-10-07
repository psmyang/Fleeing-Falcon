#pragma once
#include <vector>
#include <algorithm>


#include "GameObject.h"
#include "AniManager.h"
#include "Bullet.h"
#include "SoundManager.h"


class Fighter: public GameObject
{
public:
	Fighter();
	Fighter(const char* TextureSheet, int x, int y):GameObject(TextureSheet,x,y)
	{
		BulletInterval = 0;
	}
	//~Fighter();
	
	void Update(GameObject* PlayerFalcon);
	//void Render();
	//void Destroy();
	void ShootBullet(GameObject* PlayerFalcon);
	void BulletUpdate(GameObject *PlayerFalcon);

	std::vector<Bullet*> ComBulletVec;
private:
	
	int BulletInterval;
	const int FIGHTBULLETCD=200;
};
