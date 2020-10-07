#include "EnemyManager.h"
#include <time.h>
#include <cstdlib>
#include <iostream>

EnemyManager* EnemyManager::s_pInstance = NULL;
const int AUTOCREATEPOSY = -200;
const int WINDOWWIDTH = 800;

EnemyManager* EnemyManager::Instance()
{
	if (s_pInstance == 0)
	{
		s_pInstance = new EnemyManager();
	}

	return s_pInstance;
}

EnemyManager::EnemyManager()
{
	
}

EnemyManager::~EnemyManager()
{
	
}

void EnemyManager::CreateEnemy(EnemyType type)
{
	switch (type)
	{
	case 1:
		{
			//FighterVec.push_back(new Fighter("assest/X_Wing.png", getRanPos()[0], getRanPos()[1]));
		Fighter* TempFighter = new Fighter("assest/X_Wing.png", getRanPos()[0], getRanPos()[1]);

		//检测敌机及向量是否正常生成
		/*if(TempFighter!=nullptr)
		{
			std::cout << "Fighter Created!" << std::endl;
		}
		if (!FighterVec.empty())
		{
			std::cout << "Fighter Vec Created!" << std::endl;
		}
		else
		{
			std::cout << "NULL" << std::endl;
		}*/
			
		FighterVec.push_back(TempFighter);
		
		//delete TempFighter;
		TempFighter = nullptr;
		LastFighterCreateTime = 0;
		}
		break;
	case 2:
		break;
	default:
		break;
	}
}

void EnemyManager::Destroy(GameObject* GameObject)
{
	SDL_DestroyTexture(GameObject->getObjTex());
	delete GameObject;
	GameObject = nullptr;
}

int* EnemyManager::getRanPos()
{
	int RanPos[2];
	RanPos[1] = AUTOCREATEPOSY;
	srand((unsigned)time(NULL));
	RanPos[0] = (rand() % (WINDOWWIDTH-100))+50;
	return RanPos;
}