#pragma once
#include "ECS.h"
class Bullet {
public:
	Bullet() {}
	static void CreateBullet(b2World& phyworld, float x, float y, float angle, bool Enemy);
	
	static void AddToBulletlist(unsigned int entity);
	static void RemoveFromBulletlist(unsigned int entity);
	
	static bool DeleteCheck(unsigned int entity);

	static void update(entt::registry* reg);

	static bool damage(unsigned int entity);

	static bool IsEnemyBullet(unsigned int entity);
	bool CanItBeHitByBullet(unsigned int entity);
private:
	int speed=600;
	static std::vector<unsigned int> Bulletlist;

};

inline std::vector<unsigned int> Bullet::Bulletlist = {};
