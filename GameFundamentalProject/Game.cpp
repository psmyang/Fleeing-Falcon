#include<iostream>
#include<vector>
#include <algorithm>
#include<string.h>

#include"Game.h"
#include "AniManager.h"
#include "GameObject.h"
#include "Map.h"
#include "Bullet.h"
#include "Falcon.h"
#include "Fighter.h"
#include "Smoke.h"
#include "SoundManager.h"
#include "EnemyManager.h"
#include"TextManager.h"

Falcon* PlayerFalcon;
Map* map;

EnemyManager* enemyManager;

SDL_Renderer* Game::pRenderer = nullptr;

Game::Game()
{

}

Game::~Game()
{

}

void Game::Init(const char* WindowTitle, int xpos, int ypos, int width, int height, bool isFullScreen)
{
	int flags = 0;
	if (isFullScreen == 1)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout << "INIT SUCCESS!" << std::endl;
		pWindow = SDL_CreateWindow(WindowTitle, xpos, ypos, width, height, flags);
		if (pWindow)
		{
			pRenderer = SDL_CreateRenderer(pWindow, -1, 0);
		}
		if (pWindow && pRenderer)
		{
			std::cout << "Window and Renderer create successfully!" << std::endl;
		}
		isRunning = true;
	}
	else
	{
		isRunning = false;
		std::cout << "INIT FAILED!" << std::endl;
	}
	TextManager::Instance()->InitTTF();
}
	

void Game::Prepare()
{
	PlayerFalcon = new Falcon("assest/Falcon.png", 400, 500);
	//ComFighter = new Fighter("assest/X_Wing.png", 400,100);
	map = new Map();

	enemyManager = new EnemyManager;
	enemyManager->CreateEnemy(X_Wing);

	SoundManager::Instance()->InitAll();
	SoundManager::Instance()->PlayMusic("assest/Battle_BGM.wav", -1);
}


void Game::HandleEvents()
{
	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type) {
	case SDL_QUIT:isRunning = false;
		break;
	default:break;
	}
	if (event.type == SDL_KEYDOWN)
	{
		switch (event.key.keysym.sym)
		{
		//���Ʒɴ��ƶ��������ӵ�
		case(SDLK_SPACE):
		{
			if(PlayerFalcon==nullptr)
			{
				break;
			}
			if(PlayerFalcon->FalconBulletInterval<PlayerFalcon->getBulletCD())
			{
				break;
			}
			else
			{
				PlayerFalcon->PlayerBulletVec.push_back(new Bullet("player",PlayerFalcon->getDestRect().x+32, PlayerFalcon->getDestRect().y));
				PlayerFalcon->FalconBulletInterval = 0;
				SoundManager::Instance()->PlaySound("assest/FalconFire.wav", 0);
				break;
			}			
		}
		case(SDLK_LEFT):
		{
			if (PlayerFalcon == nullptr)
			{
				break;
			}
			if(PlayerFalcon->getDestRect().x<=0)
			{
				break;
			}
			PlayerFalcon->Move(-PlayerFalcon->getFalconSpeed(),0);
			break;
		}
		case(SDLK_RIGHT):
		{
			if (PlayerFalcon == nullptr)
			{
				break;
			}
			if (PlayerFalcon->getDestRect().x >= 750)
			{
				break;
			}
			PlayerFalcon->Move(PlayerFalcon->getFalconSpeed(), 0);
			break;
		}
		case(SDLK_UP):
		{
			if (PlayerFalcon == nullptr)
			{
				break;
			}
			if (PlayerFalcon->getDestRect().y <= 0)
			{
				break;
			}
			PlayerFalcon->Move(0,-PlayerFalcon->getFalconSpeed());
			break;
		}
		case(SDLK_DOWN):
		{
			if (PlayerFalcon == nullptr)
			{
				break;
			}
			if (PlayerFalcon->getDestRect().y >= 550)
			{
				break;
			}
			PlayerFalcon->Move(0, PlayerFalcon->getFalconSpeed());
			break;
		}

		//������������	
		case(SDLK_KP_PLUS):
		{
			SoundManager::Instance()->TurnUpVolume();
			break;
		}
		case(SDLK_KP_MINUS):
		{
			SoundManager::Instance()->TurnDownVolume();
			break;
		}

		//������Ϸ�˳�	
		case(SDLK_ESCAPE):
		{
			isRunning=false;
			break;
		}
		}
	}
}

void Game::Input()
{

}

void Game::Update()
{
	//������Ҽ��ӵ�״̬��������ٵл������µл�״̬
	if(PlayerFalcon!=nullptr)
	{
	PlayerFalcon->Update();
	for (int i = 0; i < (int)enemyManager->FighterVec.size(); i++)
		{
			if(enemyManager->FighterVec[i]!=nullptr)
			{
				PlayerFalcon->BulletUpdate(enemyManager->FighterVec[i],PLayerScore);
			}			
		}
	}

	//����ÿ�ܵл���״̬�����������ң�������ҷɻ�״̬
	for(int i = 0; i < (int)enemyManager->FighterVec.size(); i++)
	{
		if(enemyManager->FighterVec[i]!=nullptr)
		{
			enemyManager->FighterVec[i]->Update(PlayerFalcon);
			if(PlayerFalcon!=nullptr)
			{
				if(PlayerFalcon->getActive()==true)
				{
					enemyManager->FighterVec[i]->BulletUpdate(PlayerFalcon);
				}
			}
			
		}	
	}

	
	//�ж�����Ƿ���л���ײ
	if(PlayerFalcon!=nullptr)
	{
		if(PlayerFalcon->getActive()==false)
		{
			for (int i = 0; i < (int)enemyManager->FighterVec.size(); i++)
			{
				/*if(PlayerFalcon==nullptr)
				{
					std::cout << "���ý���" << std::endl;
				}*/
				if (enemyManager->FighterVec[i]->isCollidingWith(*PlayerFalcon))
				{
				std::cout << "BOOM!" << std::endl;
				PlayerFalcon->setActive(false);
				enemyManager->FighterVec[i]->setActive(false);
				}
			}
		}
	}
	

	//���ٲ����ڻ�Ծ״̬����Ϸ����
	//std::cout << enemyManager->FighterVec.size() << std::endl;
	Destroy();
	
	//ÿ��һ��ʱ���Զ�����Ļ�Ϸ����ɵл�
	enemyManager->TimeIncrease();
	if(enemyManager->getLastCreateTime()>=enemyManager->FIGHTERCREATECD)
	{
		enemyManager->CreateEnemy(X_Wing);
	}
	
	//ÿ��2s��ͼ����һ��
	map->TimeCount++;
	//std::cout << map->TimeCount << std::endl;
	if(map->TimeCount >=map->SCROLLCD)
	{
		map->ChangeMap();
		//std::cout << "Map Changed!" << std::endl;
	}


}

void Game::Render()
{
	SDL_RenderClear(pRenderer);
	map->DrawMap();
	if(PlayerFalcon!=nullptr)
	{
		//std::cout << "Falcon has not been destroied!" << PlayerFalcon<<std::endl;
		PlayerFalcon->Render();
	}
	for (int i = 0; i < (int)enemyManager->FighterVec.size(); i++)
	{
		if(enemyManager->FighterVec [i]!=nullptr)
	{
			enemyManager->FighterVec[i]->Render();
	}
	}
	

	//��Ⱦ��ҷ�����ӵ�
	if (PlayerFalcon != nullptr)
	{
		SDL_SetRenderDrawColor(pRenderer, 255, 255, 0, 0);
		for (int i = 0; i < (int)PlayerFalcon->PlayerBulletVec.size(); i++)
		{
			SDL_RenderFillRect(pRenderer, &PlayerFalcon->PlayerBulletVec[i]->DestRect);
		}
	}
	

	//��Ⱦ�л�������ӵ�
	SDL_SetRenderDrawColor(pRenderer, 255, 255, 255, 0);
	//std::cout << "size:"<<(int)enemyManager->FighterVec.size()<<std::endl;
	for(int i=0;i<(int)enemyManager->FighterVec.size();i++)
	{
		for (int j = 0; j < (int)enemyManager->FighterVec[i]->ComBulletVec.size(); j++)
		{
			SDL_RenderFillRect(pRenderer, &enemyManager->FighterVec[i]->ComBulletVec[j]->DestRect);
		}
	}

	//��ʾ��ҷ���
	std::string Score= std::to_string(PLayerScore);
	Score = "Score: " + Score;
	const char* tmpText = Score.c_str();
	TextManager::Instance()->LoadText(tmpText, 0, 0, 100, 25);
	
	AniManager::Instance()->AnimateSmoke();
	SDL_RenderPresent(pRenderer);
}

void Game::Clean()
{
	SDL_DestroyWindow(pWindow);
	SDL_DestroyRenderer(pRenderer);
	SDL_Quit();
	std::cout << "Game Cleaned!" << std::endl;
}

void Game::Quit()
{

}

void Game::Destroy()
{
	if(PlayerFalcon!=nullptr)
	{
		if(PlayerFalcon->getActive()==false)
		{
			PlayerFalcon->Destroy();
			delete PlayerFalcon;
			PlayerFalcon = nullptr;
		}
	}
	
	for(int i=0;i<enemyManager->FighterVec.size();i++)
	{
		if(enemyManager->FighterVec[i]->getActive()==false)
		{
			enemyManager->FighterVec[i]->setActive(false);
			delete enemyManager->FighterVec[i];
			enemyManager->FighterVec[i] = nullptr;
			//std::cout << "delete Fighter " << i << std::endl;
		}
	}
	if (!enemyManager->FighterVec.empty())
	{
		enemyManager->FighterVec.erase(remove(enemyManager->FighterVec.begin(), enemyManager->FighterVec.end(), nullptr), enemyManager->FighterVec.end());
	}
}