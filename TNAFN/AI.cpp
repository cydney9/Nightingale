#include "AI.h"

#include <ctime>
#include <chrono>
#include "Barrel.h"



std::chrono::steady_clock sc;

auto starttime = sc.now();
auto currenttime = sc.now();

AI::AI(unsigned int entity, int type)
{
	entityNum = entity;
	AItype = type;
	AttackTimer = 1;
	if (AItype == 0) {
		AttackCoolDown = 0.5;
		CoolDownTime = 0.5;
	}
	else if (AItype == 1) {
		AttackCoolDown = 3;
		CoolDownTime = 3;
	}
}

void AI::WalkToPlayer()
{
	auto& EBody = ECS::GetComponent<PhysicsBody>(entityNum);
	auto& EnemyAnimation = ECS::GetComponent<AnimationController>(entityNum);
	auto PlayerX = ECS::GetComponent<Transform>(EntityIdentifier::MainPlayer()).GetPositionX();
	auto EnemyX = EBody.GetBody()->GetPosition().x;

	b2Vec2 vel = b2Vec2(EBody.GetBody()->GetLinearVelocity());
	float desireVel = vel.x;

	if (EnemyX > PlayerX - 150 && EnemyX < PlayerX + 150) {
		if (AItype == 0&&IsAttack==false) {
			if (PlayerX > EnemyX) {
				desireVel = b2Max(vel.x + 0.1f, 40.f);
				EnemyAnimation.SetActiveAnim(1);
			}
			else {
				desireVel = b2Min(vel.x - 0.1f, -40.f);
				EnemyAnimation.SetActiveAnim(0);
			}
		}
		else if (AItype == 0 && IsAttack==true) {
			if (PlayerX > EnemyX) {
				EnemyAnimation.SetActiveAnim(3);
			}
			else {
				EnemyAnimation.SetActiveAnim(2);
			}
		}
		else if (AItype == 1) {
			if (PlayerX > EnemyX) {
				desireVel = b2Max(vel.x + 0.1f, 25.f);
				EnemyAnimation.SetActiveAnim(5);
			}
			else {
				desireVel = b2Min(vel.x - 0.1f, -25.f);
				EnemyAnimation.SetActiveAnim(4);
			}
		}
		float velChange = desireVel - vel.x;
		float impulse = EBody.GetBody()->GetMass() * velChange;
		EBody.GetBody()->ApplyForce(b2Vec2(impulse, 0), EBody.GetBody()->GetWorldCenter(), true);

		if (EBody.GetBody()->GetLinearVelocity().x < 3.f && EBody.GetBody()->GetLinearVelocity().x > -3.f&&EBody.GetIsGrounded()&& AItype == 0) {
			currenttime = sc.now();
			auto time_span = static_cast<std::chrono::duration<double>>(currenttime - starttime);
			if ((double)time_span.count() > 3) {
				EBody.GetBody()->ApplyForce(b2Vec2(0, 90000), EBody.GetBody()->GetWorldCenter(), true);
				starttime = sc.now();
			}
		}

	}
}

void AI::EnemyAttack()
{

	auto& EBody = ECS::GetComponent<PhysicsBody>(entityNum);
	auto& body = ECS::GetComponent<PhysicsBody>(EntityIdentifier::MainPlayer());
	auto& PlayerHP = ECS::GetComponent<HealthBar>(EntityIdentifier::MainPlayer());

	if (CanAttack==true) {
		if (EBody.GetBody()->GetPosition().x < body.GetBody()->GetPosition().x &&
			body.GetBody()->GetPosition().x<EBody.GetBody()->GetPosition().x + 30 &&
			EBody.GetBody()->GetPosition().y + 15>body.GetBody()->GetPosition().y &&
			body.GetBody()->GetPosition().y > EBody.GetBody()->GetPosition().y - 15) {
			
			CanAttack = false;
			IsAttack = true;
		}
		else if (EBody.GetBody()->GetPosition().x-30 < body.GetBody()->GetPosition().x &&
			body.GetBody()->GetPosition().x<EBody.GetBody()->GetPosition().x  &&
			EBody.GetBody()->GetPosition().y + 15>body.GetBody()->GetPosition().y &&
			body.GetBody()->GetPosition().y > EBody.GetBody()->GetPosition().y - 15) {

			CanAttack = false;
			IsAttack = true;
		}
	}

	if(IsAttack==true&& AItype==0){
		if (EBody.GetBody()->GetPosition().x < body.GetBody()->GetPosition().x &&
			body.GetBody()->GetPosition().x<EBody.GetBody()->GetPosition().x + 30 &&
			EBody.GetBody()->GetPosition().y + 15>body.GetBody()->GetPosition().y &&
			body.GetBody()->GetPosition().y > EBody.GetBody()->GetPosition().y - 15) {

			if (AttackTimer < 0.5) {
				PlayerHP.Damage(0.1f);
				PlayerHP.SetCanDamage(false);
				body.GetBody()->ApplyForce(b2Vec2(45000, 45000), body.GetBody()->GetWorldCenter(), true);
			}
		}
		else if (EBody.GetBody()->GetPosition().x - 30 < body.GetBody()->GetPosition().x &&
			body.GetBody()->GetPosition().x<EBody.GetBody()->GetPosition().x &&
			EBody.GetBody()->GetPosition().y + 15>body.GetBody()->GetPosition().y &&
			body.GetBody()->GetPosition().y > EBody.GetBody()->GetPosition().y - 15) {

			if (AttackTimer < 0.5) {
				PlayerHP.Damage(0.1f);
				PlayerHP.SetCanDamage(false);
				body.GetBody()->ApplyForce(b2Vec2(-45000, 45000), body.GetBody()->GetWorldCenter(), true);
			}
		}
	}
	else if (CanAttack == true && AItype == 1) {
		float X = ECS::GetComponent<Transform>(entityNum).GetPositionX();
		float Y = ECS::GetComponent<Transform>(entityNum).GetPositionY();
		float PlayerX = ECS::GetComponent<Transform>(EntityIdentifier::MainPlayer()).GetPosition().x;
		float PlayerY = ECS::GetComponent<Transform>(EntityIdentifier::MainPlayer()).GetPosition().y;

		float dx = X - PlayerX;
		float dy = Y - PlayerY;


		float Angle = atan2(dy, dx);
		Angle = Angle;

		b2Body *Body = ECS::GetComponent<PhysicsBody>(entityNum).GetBody();
		Bullet::CreateBullet(*Body->GetWorld(), X + (10 * cos(Angle + Transform::ToRadians(180.f))), Y + (10 * sin(Angle + Transform::ToRadians(180.f))), Angle + Transform::ToRadians(180.f), true);

		ECS::GetComponent<HorizontalScroll>(EntityIdentifier::MainCamera()).SetFocus(&ECS::GetComponent<Transform>(EntityIdentifier::MainPlayer()));
		ECS::GetComponent<VerticalScroll>(EntityIdentifier::MainCamera()).SetFocus(&ECS::GetComponent<Transform>(EntityIdentifier::MainPlayer()));
		CanAttack = false;
	}
}

void AI::Update()
{
	auto& PlayerHP = ECS::GetComponent<HealthBar>(EntityIdentifier::MainPlayer());
	if (IsAttack == true) {
		if (AttackTimer < 0) {
			int currentAnim = ECS::GetComponent<AnimationController>(entityNum).GetActiveAnim();
			ECS::GetComponent<AnimationController>(entityNum).GetAnimation(currentAnim).Reset();
			AttackTimer = 0.64;
			IsAttack = false;
			PlayerHP.SetCanDamage(true);
		}else {
			AttackTimer -= Timer::deltaTime;
		}
	}else if (CanAttack == false) {
		if (AttackCoolDown < 0) {
			AttackCoolDown = CoolDownTime;
			CanAttack = true;
		}
		else {
			AttackCoolDown-= Timer::deltaTime;
		}
	}
	BarrelRota();
	WalkToPlayer();
	EnemyAttack();
}

void AI::BarrelRota()
{
	if (AItype == 1) {
		ECS::GetComponent<Barrel>(entityNum).Update();
	}
}

void AI::SetAIType(int type)
{
	AItype = type;
}

float AI::getAttackTimer()
{
	return AttackTimer;
}

int AI::getAIType()
{
	return AItype;
}





