#pragma once
#include "ECS.h"
#include "Timer.h"

class AI
{
public:
	AI() {}
	//create an AI
	AI(unsigned int entity, int type);
	void WalkToPlayer();
	void EnemyAttack();
	void Update();
	void BarrelRota();

	void SetAIType(int type);

	float getAttackTimer();
	int getAIType();
	
	
private:
	int AItype = 0; // 0 = melee, 1 = shooter, 2 = turret, 3 = boss
	int speed=0;
	float AttackCoolDown;
	float CoolDownTime;
	unsigned int entityNum = 0;

	float AttackTimer=0.64;
	bool IsAttack = false;
	bool CanAttack = true;
};
