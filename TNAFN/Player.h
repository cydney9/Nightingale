#pragma once
#include "ContactList.h"
#include "EntityList.h"
#include "ECS.h"
class Player
{
public:
	Player() {}
	static void CreatePlayer(b2World& phyworld, int x, int y);
private:
};

