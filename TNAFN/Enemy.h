#pragma once
#include "ECS.h"
#include "ContactList.h"

class Enemy
{
	friend class PlayerActionController;
	friend class Bullet;
public:
	Enemy() {}
	static void CreateEnemy(b2World& phyworld,int x, int y ,int type);

	static void AddToEnemylist(unsigned int entity);
	static void RemoveFromEnemylist(unsigned int entity);

	static bool DeleteCheck(unsigned int entity);

	static void update(entt::registry* reg);

private:
	static std::vector<unsigned int> EnemyList;
};

inline std::vector<unsigned int> Enemy::EnemyList = {};