#pragma once
#include "ECS.h"
#include "Scene.h"
#include "BackEnd.h"

class PlayerActionController
{
public:
	static void walkLeft();
	static void walkRight();
	static void Jump();
	static void FlyUp();
	static void FlyDown();
	static void FlyLeft();
	static void FlyRight();

	static void Shoot(Scene* scene, float handangle);
	static float HandRotation(Scene* scene, SDL_MouseMotionEvent evnt);
};

