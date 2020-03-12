#include "AI.h"

#include <ctime>
#include <chrono>


std::chrono::steady_clock sc;

auto starttime = sc.now();
auto currenttime = sc.now();

AI::AI(unsigned int entity, int type)
{
	entityNum = entity;
	AItype = type;
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
		if (AItype == 0) {
			if (PlayerX > EnemyX) {
				desireVel = b2Max(vel.x + 0.1f, 50.f);
				EnemyAnimation.SetActiveAnim(1);
			}
			else {
				desireVel = b2Min(vel.x - 0.1f, -50.f);
				EnemyAnimation.SetActiveAnim(0);
			}
		}
		float velChange = desireVel - vel.x;
		float impulse = EBody.GetBody()->GetMass() * velChange;
		EBody.GetBody()->ApplyForce(b2Vec2(impulse, 0), EBody.GetBody()->GetWorldCenter(), true);

		if (EBody.GetBody()->GetLinearVelocity().x < 3.f && EBody.GetBody()->GetLinearVelocity().x > -3.f&&EBody.GetIsGrounded()) {
			currenttime = sc.now();
			auto time_span = static_cast<std::chrono::duration<double>>(currenttime - starttime);
			if ((double)time_span.count() > 3) {
				EBody.GetBody()->ApplyForce(b2Vec2(0, 3), EBody.GetBody()->GetWorldCenter(), true);
				starttime = sc.now();
			}
		}

	}
}

void AI::EnemyAttack()
{
}

void AI::Update()
{
	WalkToPlayer();
	EnemyAttack();
}

void AI::SetAIType(int type)
{
	AItype = type;
}



