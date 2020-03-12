#include "PlayerActionController.h"
#include <cmath>
void PlayerActionController::walkLeft(b2Body* body, b2Vec2 vel, float desireVel)
{
	desireVel = b2Min(vel.x - 0.2f, -10.f);

	float velChange = desireVel - vel.x;
	float impulse = body->GetMass() * velChange;
	body->ApplyLinearImpulse(b2Vec2(impulse, 0), body->GetWorldCenter(), true);
	if (body->GetLinearVelocity().x < -10) {
		body->SetLinearVelocity(b2Vec2(-10, body->GetLinearVelocity().y));
	}
}

void PlayerActionController::walkRight(b2Body* body, b2Vec2 vel, float desireVel)
{
	desireVel = b2Max(vel.x + 0.2f, 10.f);

	float velChange = desireVel - vel.x;
	float impulse = body->GetMass() * velChange;
	body->ApplyLinearImpulse(b2Vec2(impulse, 0), body->GetWorldCenter(), true);
	if (body->GetLinearVelocity().x > 10) {
		body->SetLinearVelocity(b2Vec2(10, body->GetLinearVelocity().y));
	}
}

void PlayerActionController::Jump(b2Body* body)
{
	body->ApplyForce(b2Vec2(0, 560000), body->GetWorldCenter(), true);
}

void PlayerActionController::FlyUp(b2Body* body)
{
	body->ApplyForce(b2Vec2(0, 90000), body->GetWorldCenter(), false);

	if (body->GetLinearVelocity().y > 5) {
		body->SetLinearVelocity(b2Vec2(body->GetLinearVelocity().x, 5));
	}
}

void PlayerActionController::FlyDown(b2Body* body)
{
	body->ApplyForce(b2Vec2(0, -50000), body->GetWorldCenter(), false);

	if (body->GetLinearVelocity().y < -5) {
		body->SetLinearVelocity(b2Vec2(body->GetLinearVelocity().x, -5));
	}

}

void PlayerActionController::FlyLeft(b2Body* body)
{
	body->ApplyForce(b2Vec2(-32000, 0), body->GetWorldCenter(), false);

	if (body->GetLinearVelocity().x < -15) {
		body->SetLinearVelocity(b2Vec2(-15, body->GetLinearVelocity().y));
	}
}

void PlayerActionController::FlyRight(b2Body* body)
{
	body->ApplyForce(b2Vec2(32000, 0), body->GetWorldCenter(), false);

	if (body->GetLinearVelocity().x > 15) {
		body->SetLinearVelocity(b2Vec2(15, body->GetLinearVelocity().y));
	}
}

void PlayerActionController::Shoot(Scene* scene,float handangle)
{
	float WH_X = ECS::GetComponent<Transform>(EntityIdentifier::WeaponHand()).GetPositionX();
	float WH_Y = ECS::GetComponent<Transform>(EntityIdentifier::WeaponHand()).GetPositionY();
	float WH_angle = ECS::GetComponent<Transform>(EntityIdentifier::WeaponHand()).GetRotationAngleZ();

	Bullet::CreateBullet(scene->GetPhysicsWorld(), WH_X + (10 * cos(handangle + Transform::ToRadians(180.f))), WH_Y + (10 * sin(handangle + Transform::ToRadians(180.f))), handangle + Transform::ToRadians(180.f));

	ECS::GetComponent<HorizontalScroll>(EntityIdentifier::MainCamera()).SetFocus(&ECS::GetComponent<Transform>(EntityIdentifier::MainPlayer()));
	ECS::GetComponent<VerticalScroll>(EntityIdentifier::MainCamera()).SetFocus(&ECS::GetComponent<Transform>(EntityIdentifier::MainPlayer()));
}

float PlayerActionController::HandRotation(Scene* scene, SDL_MouseMotionEvent evnt)
{
	//printf("Mouse Moved（%f, %f）\n", float(evnt.x), float(evnt.y));
	scene->MouseMotion(evnt);
	Camera tempCam = ECS::GetComponent<Camera>(EntityIdentifier::MainCamera());
	vec2 windowSpace = vec2(float(BackEnd::GetWindowWidth()), float(BackEnd::GetWindowHeight()));
	vec2 position = vec2(tempCam.GetPositionX(), tempCam.GetPositionY());

	vec2 clickedPoint = vec2(
		(evnt.x / windowSpace.x - 0.5f) * tempCam.GetAspect() * tempCam.GetOrthoSize().w * 2,
		-(evnt.y / windowSpace.y - 0.5f) * tempCam.GetOrthoSize().w * 2
	);
	clickedPoint = clickedPoint + position;

	auto playerBodyPos = ECS::GetComponent<PhysicsBody>(EntityIdentifier::MainPlayer()).GetPosition();

	vec2 convertedMouse = clickedPoint;

	float dx = playerBodyPos.x - convertedMouse.x;
	float dy = playerBodyPos.y - convertedMouse.y;


	float playerDir = atan2(dy, dx);

	ECS::GetComponent<Transform>(EntityIdentifier::WeaponHand()).SetRotationAngleZ(playerDir + Transform::ToRadians(180.f));

	return playerDir;
}

void PlayerActionController::CBTimer()
{
	if (PlayingCombo == 1) {
		Combo1Timer -= Timer::deltaTime;
	}else if (PlayingCombo == 2) {
		Combo2Timer -= Timer::deltaTime;
	}else if (PlayingCombo == 3) {
		Combo3Timer -= Timer::deltaTime;
	}
}

bool PlayerActionController::ComboCheck()
{
	if (Combo1Timer < 0 || Combo2Timer < 0 || Combo3Timer < 0) {
		if (Combo1Timer < 0) {
			if (wantNextCombo) {
				PlayingCombo = 2;
			}
			else {
				PlayingCombo = 0;
			}
			ChargeCoolDown = true;
			wantNextCombo = false;
			Combo1Timer = 0.72;
		}
		if (Combo2Timer < 0) {
			if (wantNextCombo) {
				PlayingCombo = 3;
			}
			else {
				PlayingCombo = 0;
			}
			ChargeCoolDown = true;
			wantNextCombo = false;
			Combo2Timer = 0.40;
		}
		if (Combo3Timer < 0) {
			ChargeCoolDown = true;
			wantNextCombo = false;
			PlayingCombo = 0;
			Combo3Timer = 0.48;
		}
		return true;
	}
	auto body = ECS::GetComponent<PhysicsBody>(EntityIdentifier::MainPlayer()).GetBody();
	return false;
}

int PlayerActionController::WhatIsPlayingNow()
{
	if (Combo1Timer < 0.7166) {
		return 1;
	}
	else if (Combo2Timer < 0.3999) {
		return 2;
	}
	else if (Combo3Timer < 0.4799) {
		return 3;
	}
	else {
		return 0;
	}
}

void PlayerActionController::UpdateAttack()
{
	auto body = ECS::GetComponent<PhysicsBody>(EntityIdentifier::MainPlayer()).GetBody();
	if (WhatIsPlayingNow() == 0) {
		PlayingCombo = 1;
	}
	else if (WhatIsPlayingNow() == 1) {
		wantNextCombo = true;
	}
	else if (WhatIsPlayingNow() == 2) {
		wantNextCombo = true;

	}else if (WhatIsPlayingNow() == 3) {
		wantNextCombo = false;
	}
}

int PlayerActionController::getPlayingCombo()
{
	return PlayingCombo;
}

bool PlayerActionController::IsCombo()
{
	if (WhatIsPlayingNow() != 0) {
		return true;
	}
	return false;
}

void PlayerActionController::Charge(b2Body* body,int LOR)
{
	ClosestEnemy = NULL;
	for (int x(0); x < Enemy::EnemyList.size(); x++) {
		if (InAttackRangeCheck(Enemy::EnemyList[x])) {
			if (ClosestEnemy == NULL) {
				ClosestEnemy = Enemy::EnemyList[x];
			}
			else {
				ClosestEnemy=DistanceCheck(ClosestEnemy, Enemy::EnemyList[x]);
			}
		}
	}
	if (ClosestEnemy != NULL) {
		AttackAngle=AttackAngleCheck(ClosestEnemy);
	}
	else {
		AttackAngle = LOR > 0 ? 0 : 180;
	}

	if (ChargeCoolDown == true && WhatIsPlayingNow() != 0) {
		body->ApplyForce(b2Vec2(1000000 * cos(AttackAngle), 1000000 * sin(AttackAngle)), body->GetWorldCenter(), true);
		if (body->GetLinearVelocity().x  > 20 ) {
			body->SetLinearVelocity(b2Vec2(20 , body->GetLinearVelocity().y));
		}
		if (body->GetLinearVelocity().x  < -20 ) {
			body->SetLinearVelocity(b2Vec2(-20 , body->GetLinearVelocity().y));
		}
		if (body->GetLinearVelocity().y  > 20 ) {
			body->SetLinearVelocity(b2Vec2(body->GetLinearVelocity().x, 20 ));
		}
		if (body->GetLinearVelocity().y  < -20 ) {
			body->SetLinearVelocity(b2Vec2(body->GetLinearVelocity().x, -20 ));
		}
		ChargeCoolDown = false;
	}
	else if (WhatIsPlayingNow() != 0) {
		if (Combo1Timer < 0.3|| Combo2Timer < 0.2|| Combo3Timer < 0.2) {
			body->SetLinearVelocity(b2Vec2(3* cos(AttackAngle), 3 * sin(AttackAngle)));
		}
	}

}

bool PlayerActionController::InAttackRangeCheck(unsigned int entity)
{
	auto& EnemyphysicsBod = ECS::GetComponent<PhysicsBody>(entity);

	float PlayerX = ECS::GetComponent<Transform>(EntityIdentifier::MainPlayer()).GetPositionX();
	float PlayerY = ECS::GetComponent<Transform>(EntityIdentifier::MainPlayer()).GetPositionY();
	float EnemyX = EnemyphysicsBod.GetBody()->GetPosition().x;
	float EnemyY = EnemyphysicsBod.GetBody()->GetPosition().y;
	if ((PlayerX+100>EnemyX &&PlayerX-100<EnemyX)&& (PlayerY + 100 > EnemyY && PlayerY - 100 < EnemyY)) {
		return true;
	}
	else {
		return false;
	}
}

int PlayerActionController::DistanceCheck(unsigned int CEntity, unsigned int entity)
{
	auto& C_EntityphysicsBod = ECS::GetComponent<PhysicsBody>(CEntity);
	auto& EntityphysicsBod = ECS::GetComponent<PhysicsBody>(entity);

	float PlayerX = ECS::GetComponent<Transform>(EntityIdentifier::MainPlayer()).GetPositionX();
	float PlayerY = ECS::GetComponent<Transform>(EntityIdentifier::MainPlayer()).GetPositionY();

	float C_EnemyX = C_EntityphysicsBod.GetBody()->GetPosition().x;
	float C_EnemyY = C_EntityphysicsBod.GetBody()->GetPosition().y;

	float EnemyX = EntityphysicsBod.GetBody()->GetPosition().x;
	float EnemyY = EntityphysicsBod.GetBody()->GetPosition().y;


	float C_Distance = sqrt(pow((C_EnemyX - PlayerX),2)+ pow((C_EnemyY - PlayerY),2));
	float Distance = sqrt(pow((EnemyX - PlayerX), 2) + pow((EnemyY - PlayerY), 2));

	return C_Distance>Distance? CEntity: entity;
}

float PlayerActionController::AttackAngleCheck(unsigned int entity)
{
	auto& EnemyphysicsBod = ECS::GetComponent<PhysicsBody>(entity);

	float PlayerX = ECS::GetComponent<Transform>(EntityIdentifier::MainPlayer()).GetPositionX();
	float PlayerY = ECS::GetComponent<Transform>(EntityIdentifier::MainPlayer()).GetPositionY();
	float EnemyX = EnemyphysicsBod.GetBody()->GetPosition().x;
	float EnemyY = EnemyphysicsBod.GetBody()->GetPosition().y;

	float Angle = atan2(PlayerY-EnemyY, PlayerX-EnemyX);
	return Angle + Transform::ToRadians(180.f);
}

float PlayerActionController::EnemySide(int LOR)// -1 = left, 1 = right
{
	if (ClosestEnemy != NULL) {
		auto& EnemyphysicsBod = ECS::GetComponent<PhysicsBody>(ClosestEnemy);
		float PlayerX = ECS::GetComponent<Transform>(EntityIdentifier::MainPlayer()).GetPositionX();
		float EnemyX = EnemyphysicsBod.GetBody()->GetPosition().x;
		if (EnemyX - PlayerX < 0) {//Enemy on right
			return -1;
		}
		else {
			return 1;
		}
	}
	else {
		return LOR;
	}
}

