#include "Falcon.h"

#include <iostream>
#include <ostream>


void Falcon::Update()
{
	SrcRect.w = 64;
	SrcRect.h = 64;
	SrcRect.x = 0;
	SrcRect.y = 0;

	DestRect.w = SrcRect.w;
	DestRect.h = SrcRect.h;
	//DestRect.x = xpos;
	//DestRect.y = ypos;

	FalconBulletInterval++;
}

/*void Falcon::Destroy()
{
	SDL_Rect TempRect = DestRect;
	SDL_DestroyTexture(ObjTexture);
	AniManager::Instance()->AddSmoke(Game::pRenderer, TempRect);
}*/

void Falcon::BulletUpdate(GameObject* ComFighter,int& PlayerScore)
{
	for (int i = 0; i < (int)PlayerBulletVec.size(); i++)
	{
		PlayerBulletVec[i]->PlayerUpdate();
		if (PlayerBulletVec[i]->isActive == false)
		{
			delete PlayerBulletVec[i];
			PlayerBulletVec[i] = nullptr;
		}
	}
	if (!PlayerBulletVec.empty())
	{
		PlayerBulletVec.erase(remove(PlayerBulletVec.begin(), PlayerBulletVec.end(), nullptr), PlayerBulletVec.end());
	}


	for (int i = 0; i < (int)PlayerBulletVec.size(); i++)
	{
		if (PlayerBulletVec[i]->isCollidingWith(*ComFighter))
		{
			std::cout << "Fighter Crashed!" << std::endl;
			PlayerBulletVec[i]->isActive = false;
			ComFighter->setActive(false);
			PlayerScore++;
			ComFighter->Destroy();
			/*delete ComFighter;
			ComFighter = nullptr;*/
		}
	}
}