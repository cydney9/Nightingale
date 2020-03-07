#pragma once
#include "ECS.h"
#include "EntityList.h"
class Bullet {
public:
	Bullet() {}
	static void CreateBullet(b2World& phyworld, float x, float y, float angle);
	
	static void AddToBulletlist(unsigned int entity);
	static void RemoveFromBulletlist(unsigned int entity);
	
	static bool DeleteCheck(unsigned int entity);

	static void update(entt::registry* reg);



private:
	int speed=600;
	int angle=0;
	static std::vector<unsigned int> Bulletlist;
};

inline std::vector<unsigned int> Bullet::Bulletlist = {};
