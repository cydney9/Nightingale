#pragma once
#include "ECS.h"
#include <chrono>
#include <ctime>

class AI
{
public:
	//create an AI
	AI() {};
	AI(unsigned int entity, int type);
	void WalkToPlayer();
	void EnemyAttack();
	void Update();

	void SetAIType(int type);

private:
	int AItype = 0; // 0 = melee, 1 = shooter, 2 = turret, 3 = boss
	int speed=0;
	double ReactionTime=0.5;

	unsigned int entityNum = 0;
};