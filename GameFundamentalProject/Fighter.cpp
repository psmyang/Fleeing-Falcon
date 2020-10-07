#include "Fighter.h"

#include <iostream>



const int FIGHTERSPEEDX = 1;
const int FIGHTERSPEEDY = 1;
bool FighterHorDir = true;

void Fighter::Update(GameObject* PlayerFalcon)
{
	SrcRect.w = 64;
	SrcRect.h = 64;
	SrcRect.x = 0;
	SrcRect.y = 0;

	DestRect.w = SrcRect.w;
	DestRect.h = SrcRect.h;
	//DestRect.x = xpos;
	//DestRect.y = ypos;

	BulletInterval++;
	//std::cout << BulletInterval << std::endl;

	//飞机碰到边缘改变飞行方向
	if(DestRect.x<=0||DestRect.x>=730)
	{
		FighterHorDir = !FighterHorDir;
		//std::cout << "改变飞行方向!\n"<<FighterHorDir;
	}
	
	//根据飞行方向进行横向移动
	switch (FighterHorDir)
	{
	case true:
		DestRect.x +=FIGHTERSPEEDX;
		DestRect.y += FIGHTERSPEEDY;
		//std::cout << "向右飞了。\n" << DestRect.x << " " << DestRect.y << std::endl;
		break;
	case false:
		DestRect.x -= FIGHTERSPEEDX;
		DestRect.y += FIGHTERSPEEDY;
		//std::cout << "向左飞了。\n" << DestRect.x << " " << DestRect.y << std::endl;
		break;
	default:
		break;
	}
	if(BulletInterval>=FIGHTBULLETCD)
	{
		if(PlayerFalcon!=nullptr)
			ShootBullet(PlayerFalcon);
	}
}


void Fighter::ShootBullet(GameObject* PlayerFalcon)
{
	ComBulletVec.push_back(new Bullet("fighter",DestRect.x + 32, DestRect.y+70,PlayerFalcon->getDestRect()));
	//std::cout << (int)ComBulletVec.size() << std::endl;
	SoundManager::Instance()->PlaySound("assest/FighterFire.wav", 0);
	BulletInterval = 0;
}

void Fighter::BulletUpdate(GameObject *PlayerFalcon)
{
	for (int i = 0; i < (int)ComBulletVec.size(); i++)
	{
		ComBulletVec[i]->ComUpdate();
		if (ComBulletVec[i]->isActive == false)
		{
			delete ComBulletVec[i];
			ComBulletVec[i] = nullptr;
		}
	}

	if (!ComBulletVec.empty())
	{
		ComBulletVec.erase(remove(ComBulletVec.begin(), ComBulletVec.end(), nullptr), ComBulletVec.end());
	}
	for (int i = 0; i < (int)ComBulletVec.size(); i++)
	{
		if (ComBulletVec[i]->isCollidingWith(*PlayerFalcon))
		{
			std::cout << "Falcon Crashed!" << std::endl;
			ComBulletVec[i]->isActive = false;
			PlayerFalcon->setActive(false);
			PlayerFalcon->Destroy();
			/*delete PlayerFalcon;
			PlayerFalcon = nullptr;*/
		}
	}
}

/*void Fighter::Destroy()
{
	SDL_Rect TempRect = DestRect;
	SDL_DestroyTexture(ObjTexture);
	AniManager::Instance()->AddSmoke(Game::pRenderer, TempRect);
}*/