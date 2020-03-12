#pragma once
#include "ECS.h"
#include "Scene.h"
#include "BackEnd.h"
#include "Enemy.h"


static float Combo1Timer = 0.72;
static float Combo2Timer = 0.40;
static float Combo3Timer = 0.48;

static float DashTimer = 0.28;
static float DashCoolDown = 1;

static bool IsDashing = false;

static bool CanDash = true;

static int Dashside;

static bool wantNextCombo = false;

static int PlayingCombo = 0;
static bool NextCombo = 1;

static bool ChargeCoolDown= true;
static int ClosestEnemy=NULL;
static float AttackAngle =0;

class PlayerActionController
{
public:
	static void walkLeft(b2Body *body, b2Vec2 vel, float desireVel);
	static void walkRight(b2Body* body, b2Vec2 vel, float desireVel);
	static void Jump(b2Body* body);
	static void FlyUp(b2Body* body);
	static void FlyDown(b2Body* body);
	static void FlyLeft(b2Body* body);
	static void FlyRight(b2Body* body);

	static void Shoot(Scene* scene, float handangle);
	static float HandRotation(Scene* scene, SDL_MouseMotionEvent evnt);


	static void CBTimer();

	static bool ComboCheck();

	static int WhatIsPlayingNow();

	static void UpdateAttack();

	static int getPlayingCombo();

	static bool IsCombo();

	static void Charge(b2Body* body,int LOR);

	static bool InAttackRangeCheck(unsigned int entity);

	static int DistanceCheck(unsigned int Cenemy, unsigned int entity);

	static float AttackAngleCheck(unsigned int entity);

	static float EnemySide(int LOR);

	static void Dash(int LOR);

	static void DashUpdate(b2Body* body);

	static bool IsDash();

	static int DashingSide();
};

