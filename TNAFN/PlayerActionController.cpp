#include "PlayerActionController.h"
#include "HealthBar.h"
void PlayerActionController::walkLeft(b2Body* body, b2Vec2 vel, float desireVel, Sound2D* walk)
{
	desireVel = b2Min(vel.x - 0.2f, -10.f);

	float velChange = desireVel - vel.x;
	float impulse = body->GetMass() * velChange;
	body->ApplyLinearImpulse(b2Vec2(impulse, 0), body->GetWorldCenter(), true);
	if (body->GetLinearVelocity().x < -10) {
		body->SetLinearVelocity(b2Vec2(-10, body->GetLinearVelocity().y));
	}
	if (walk->isPlaying()==false) {
		walk->play();
	}

}

void PlayerActionController::walkRight(b2Body* body, b2Vec2 vel, float desireVel, Sound2D* walk)
{
	desireVel = b2Max(vel.x + 0.2f, 10.f);

	float velChange = desireVel - vel.x;
	float impulse = body->GetMass() * velChange;
	body->ApplyLinearImpulse(b2Vec2(impulse, 0), body->GetWorldCenter(), true);
	if (body->GetLinearVelocity().x > 10) {
		body->SetLinearVelocity(b2Vec2(10, body->GetLinearVelocity().y));
	}
	if (walk->isPlaying()==false) {
		walk->play();
	}
}

void PlayerActionController::Jump(b2Body* body)
{
	body->ApplyForce(b2Vec2(0, 560000), body->GetWorldCenter(), true);
}

void PlayerActionController::FlyUp(b2Body* body)
{
	body->ApplyForce(b2Vec2(0, 90000), body->GetWorldCenter(), true);
	ECS::GetComponent<HealthBar>(EntityIdentifier::MainPlayer()).powerDown();
	if (body->GetLinearVelocity().y > 5) {
		body->SetLinearVelocity(b2Vec2(body->GetLinearVelocity().x, 5));
	}
}

void PlayerActionController::FlyDown(b2Body* body)
{
	body->ApplyForce(b2Vec2(0, -50000), body->GetWorldCenter(), true);
	ECS::GetComponent<HealthBar>(EntityIdentifier::MainPlayer()).powerDown();
	if (body->GetLinearVelocity().y < -5) {
		body->SetLinearVelocity(b2Vec2(body->GetLinearVelocity().x, -5));
	}

}

void PlayerActionController::FlyLeft(b2Body* body)
{
	body->ApplyForce(b2Vec2(-32000, 0), body->GetWorldCenter(), true);
	ECS::GetComponent<HealthBar>(EntityIdentifier::MainPlayer()).powerDown();
	if (body->GetLinearVelocity().x < -15) {
		body->SetLinearVelocity(b2Vec2(-15, body->GetLinearVelocity().y));
	}
}

void PlayerActionController::FlyRight(b2Body* body)
{
	body->ApplyForce(b2Vec2(32000, 0), body->GetWorldCenter(), true);
	ECS::GetComponent<HealthBar>(EntityIdentifier::MainPlayer()).powerDown();
	if (body->GetLinearVelocity().x > 15) {
		body->SetLinearVelocity(b2Vec2(15, body->GetLinearVelocity().y));
	}
}

void PlayerActionController::Shoot(Scene* scene, float handangle)
{
	if (ECS::GetComponent<HealthBar>(EntityIdentifier::MainPlayer()).getAmmo() > 0)
	{
		ECS::GetComponent<HealthBar>(EntityIdentifier::MainPlayer()).ammoDown();
		float WH_X = ECS::GetComponent<Transform>(EntityIdentifier::WeaponHand()).GetPositionX();
		float WH_Y = ECS::GetComponent<Transform>(EntityIdentifier::WeaponHand()).GetPositionY();
		float WH_angle = ECS::GetComponent<Transform>(EntityIdentifier::WeaponHand()).GetRotationAngleZ();
		Bullet::CreateBullet(scene->GetPhysicsWorld(), WH_X + (10 * cos(handangle + Transform::ToRadians(180.f))), WH_Y + (10 * sin(handangle + Transform::ToRadians(180.f))), handangle + Transform::ToRadians(180.f), false);
		ECS::GetComponent<HorizontalScroll>(EntityIdentifier::MainCamera()).SetFocus(&ECS::GetComponent<Transform>(EntityIdentifier::MainPlayer()));
		ECS::GetComponent<VerticalScroll>(EntityIdentifier::MainCamera()).SetFocus(&ECS::GetComponent<Transform>(EntityIdentifier::MainPlayer()));
	}
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

bool PlayerActionController::ComboCheck(Sound2D* sword)
{
	if (Combo1Timer < 0 || Combo2Timer < 0 || Combo3Timer < 0) {
		if (Combo1Timer < 0) {
			if (wantNextCombo) {
				PlayingCombo = 2;
				sword->play();
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
				sword->play();
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

		for (int x(0); x < Enemy::EnemyList.size(); x++) {
			auto &Enemy = ECS::GetComponent<HealthBar>(Enemy::EnemyList[x]);
			Enemy.SetCanDamage(true);
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

void PlayerActionController::UpdateAttack(Sound2D* sword)
{

	auto body = ECS::GetComponent<PhysicsBody>(EntityIdentifier::MainPlayer()).GetBody();
	if (WhatIsPlayingNow() == 0) {
		PlayingCombo = 1;
		sword->play();
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

void PlayerActionController::Dash(int LOR)
{
	if (CanDash == true) {
		CanDash = false;
		IsDashing = true;
		Dashside = LOR;
	}
}

void PlayerActionController::DashUpdate(b2Body* body)
{
	if (DashTimer<0) {
		ECS::GetComponent<HealthBar>(EntityIdentifier::MainPlayer()).SetCanDamage(true);
		DashTimer = 0.28;
		body->SetLinearVelocity(b2Vec2(3* Dashside, 0));
		for (int x(0); x < Enemy::EnemyList.size(); x++) {
			auto& EnemyHP = ECS::GetComponent<HealthBar>(Enemy::EnemyList[x]);
			EnemyHP.SetCanDamage(true);
		}
		IsDashing = false;
	}

	if (IsDashing == true) {
		ECS::GetComponent<HealthBar>(EntityIdentifier::MainPlayer()).SetCanDamage(false);
		body->SetLinearVelocity(b2Vec2(50* Dashside, 0));
		for (int x(0); x < Enemy::EnemyList.size(); x++) {
			auto& EnemyphysicsBod = ECS::GetComponent<PhysicsBody>(Enemy::EnemyList[x]);
			auto& EnemyHP = ECS::GetComponent<HealthBar>(Enemy::EnemyList[x]);
			if (body->GetPosition().x - 17 < EnemyphysicsBod.GetBody()->GetPosition().x &&
				EnemyphysicsBod.GetBody()->GetPosition().x  < body->GetPosition().x+17 &&
				body->GetPosition().y + 15 > EnemyphysicsBod.GetBody()->GetPosition().y &&
				EnemyphysicsBod.GetBody()->GetPosition().y > body->GetPosition().y - 15) {
				EnemyHP.Damage(0.1f);
				EnemyHP.SetCanDamage(false);
			}
		}


		DashTimer -= Timer::deltaTime;
	}
	if (IsDashing == false && CanDash == false && DashCoolDown>0) {
		DashCoolDown-= Timer::deltaTime;
	}
	else if (DashCoolDown < 0) {
		DashCoolDown = 1;
		CanDash = true;
	}

}

bool PlayerActionController::IsDash()
{
	if (DashTimer < 0.279999999) {
		return true;
	}
	return false;
}

int PlayerActionController::DashingSide()
{
	return Dashside;
}

void PlayerActionController::Lockback(b2Body* body,int LOR)
{
	if (PlayingCombo ==1&& Combo1Timer<0.6) {
		for (int x(0); x < Enemy::EnemyList.size(); x++) {
			auto& EnemyphysicsBod = ECS::GetComponent<PhysicsBody>(Enemy::EnemyList[x]);
			auto& EnemyHP = ECS::GetComponent<HealthBar>(Enemy::EnemyList[x]);
			if (EnemySide(LOR) == -1) {
				if (body->GetPosition().x - 60 < EnemyphysicsBod.GetBody()->GetPosition().x&&
					EnemyphysicsBod.GetBody()->GetPosition().x<body->GetPosition().x &&
					body->GetPosition().y + 40>EnemyphysicsBod.GetBody()->GetPosition().y&&
					EnemyphysicsBod.GetBody()->GetPosition().y>body->GetPosition().y-40) {

					EnemyphysicsBod.GetBody()->ApplyLinearImpulse(b2Vec2(-270 ,0), body->GetWorldCenter(), true);
					EnemyHP.Damage(0.1f);
					EnemyHP.SetCanDamage(false);
				}
			}
			else {
				if (body->GetPosition().x + 60 > EnemyphysicsBod.GetBody()->GetPosition().x &&
					EnemyphysicsBod.GetBody()->GetPosition().x>body->GetPosition().x &&
					body->GetPosition().y + 40>EnemyphysicsBod.GetBody()->GetPosition().y &&
					EnemyphysicsBod.GetBody()->GetPosition().y > body->GetPosition().y - 40) {

					EnemyphysicsBod.GetBody()->ApplyLinearImpulse(b2Vec2(270,0), body->GetWorldCenter(), true);
					EnemyHP.Damage(0.1f);
					EnemyHP.SetCanDamage(false);
				}
			}
		}
	}else if (PlayingCombo == 2 && Combo2Timer < 0.3) {
		for (int x(0); x < Enemy::EnemyList.size(); x++) {
			auto& EnemyphysicsBod = ECS::GetComponent<PhysicsBody>(Enemy::EnemyList[x]);
			auto& EnemyHP = ECS::GetComponent<HealthBar>(Enemy::EnemyList[x]);
			if (EnemySide(LOR) == -1) {
				if (body->GetPosition().x - 60 < EnemyphysicsBod.GetBody()->GetPosition().x &&
					EnemyphysicsBod.GetBody()->GetPosition().x<body->GetPosition().x &&
					body->GetPosition().y + 40>EnemyphysicsBod.GetBody()->GetPosition().y &&
					EnemyphysicsBod.GetBody()->GetPosition().y > body->GetPosition().y - 40) {

					EnemyphysicsBod.GetBody()->ApplyLinearImpulse(b2Vec2(-270, 0), body->GetWorldCenter(), true);
					EnemyHP.Damage(0.1f);
					EnemyHP.SetCanDamage(false);
				}
			}
			else {
				if (body->GetPosition().x + 60 > EnemyphysicsBod.GetBody()->GetPosition().x &&
					EnemyphysicsBod.GetBody()->GetPosition().x > body->GetPosition().x &&
					body->GetPosition().y + 40 > EnemyphysicsBod.GetBody()->GetPosition().y &&
					EnemyphysicsBod.GetBody()->GetPosition().y > body->GetPosition().y - 40) {

					EnemyphysicsBod.GetBody()->ApplyLinearImpulse(b2Vec2(270, 0), body->GetWorldCenter(), true);
					EnemyHP.Damage(0.1f);
					EnemyHP.SetCanDamage(false);
				}
			}
		}
	}
	else if (PlayingCombo == 3 && Combo3Timer < 0.4) {
		for (int x(0); x < Enemy::EnemyList.size(); x++) {
			auto& EnemyphysicsBod = ECS::GetComponent<PhysicsBody>(Enemy::EnemyList[x]);
			auto& EnemyHP = ECS::GetComponent<HealthBar>(Enemy::EnemyList[x]);
			if (EnemySide(LOR) == -1) {
				if (body->GetPosition().x - 60 < EnemyphysicsBod.GetBody()->GetPosition().x &&
					EnemyphysicsBod.GetBody()->GetPosition().x<body->GetPosition().x &&
					body->GetPosition().y + 40>EnemyphysicsBod.GetBody()->GetPosition().y &&
					EnemyphysicsBod.GetBody()->GetPosition().y > body->GetPosition().y - 40) {

					EnemyHP.Damage(0.1f);
					EnemyphysicsBod.GetBody()->ApplyForce(b2Vec2(0, 14000), body->GetWorldCenter(), true);
					EnemyphysicsBod.GetBody()->ApplyLinearImpulse(b2Vec2(-540 , 0), body->GetWorldCenter(), true);
					EnemyHP.SetCanDamage(false);
				}
			}
			else {
				if (body->GetPosition().x + 60 > EnemyphysicsBod.GetBody()->GetPosition().x &&
					EnemyphysicsBod.GetBody()->GetPosition().x > body->GetPosition().x &&
					body->GetPosition().y + 40 > EnemyphysicsBod.GetBody()->GetPosition().y &&
					EnemyphysicsBod.GetBody()->GetPosition().y > body->GetPosition().y - 40) {

					EnemyHP.Damage(0.1f);
					EnemyphysicsBod.GetBody()->ApplyForce(b2Vec2(0, 14000), body->GetWorldCenter(), true);
					EnemyphysicsBod.GetBody()->ApplyLinearImpulse(b2Vec2(540 , 0) , body->GetWorldCenter(), true);
					EnemyHP.SetCanDamage(false);
				}
			}
		}
	}
}

float PlayerActionController::getCombo1Timer()
{
	return Combo1Timer;
}

float PlayerActionController::getCombo2Timer()
{
	return Combo2Timer;
}

float PlayerActionController::getCombo3Timer()
{
	return Combo3Timer;
}



