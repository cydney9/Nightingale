#pragma once
#include "ECS.h"
#include "ContactList.h"
#include "EntityList.h"
class Enemy
{
public:
	Enemy() {}
	static void CreateEnemy(b2World& phyworld,int x, int y ,int type);
private:
	int HP = 3;
};

