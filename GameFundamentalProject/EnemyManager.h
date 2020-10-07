#pragma once
#include <vector>
#include "Fighter.h"

enum EnemyType
{
	X_Wing=1,Boss
};

class EnemyManager
{
public:
	EnemyManager();
	~EnemyManager();

	void CreateEnemy(EnemyType type);
	void Destroy(GameObject* GameObject);
	static EnemyManager* Instance();
	int* getRanPos();
	void TimeIncrease() { LastFighterCreateTime++; }
	int getLastCreateTime() const { return LastFighterCreateTime; }

	std::vector<Fighter*> FighterVec;

	const int FIGHTERCREATECD = 400;
private:
	static EnemyManager* s_pInstance;

	int LastFighterCreateTime=0;
};
