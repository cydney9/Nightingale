#include "PlayerActionController.h"

void PlayerActionController::walkLeft()
{
	auto body = ECS::GetComponent<PhysicsBody>(EntityIdentifier::MainPlayer()).GetBody();
	auto PlayerAnim = ECS::GetComponent<AnimationController>(EntityIdentifier::MainPlayer());
	//Keyboard button held

	b2Vec2 vel = b2Vec2(body->GetLinearVelocity());
	float desireVel = body->GetLinearVelocity().x;
	desireVel = b2Min(vel.x - 6.4f, -32.f);

	float velChange = desireVel - vel.x;
	float impulse = body->GetMass() * velChange;
	body->ApplyLinearImpulse(b2Vec2(impulse, 0), body->GetWorldCenter(), true);
	if (body->GetLinearVelocity().x < -240) {
		body->SetLinearVelocity(b2Vec2(-240, body->GetLinearVelocity().y));
	}
}

void PlayerActionController::walkRight()
{
	auto body = ECS::GetComponent<PhysicsBody>(EntityIdentifier::MainPlayer()).GetBody();
	auto PlayerAnim = ECS::GetComponent<AnimationController>(EntityIdentifier::MainPlayer());
	//Keyboard button held

	b2Vec2 vel = b2Vec2(body->GetLinearVelocity());
	float desireVel = body->GetLinearVelocity().x;
	desireVel = b2Max(vel.x + 6.4f, 32.f);

	float velChange = desireVel - vel.x;
	float impulse = body->GetMass() * velChange;
	body->ApplyLinearImpulse(b2Vec2(impulse, 0), body->GetWorldCenter(), true);
	if (body->GetLinearVelocity().x > 240) {
		body->SetLinearVelocity(b2Vec2(240, body->GetLinearVelocity().y));
	}
}

void PlayerActionController::Jump()
{
	auto body = ECS::GetComponent<PhysicsBody>(EntityIdentifier::MainPlayer()).GetBody();
	body->ApplyForce(b2Vec2(0, 9600000), body->GetWorldCenter(), true);
}

void PlayerActionController::FlyUp()
{
	auto body = ECS::GetComponent<PhysicsBody>(EntityIdentifier::MainPlayer()).GetBody();
	body->ApplyForce(b2Vec2(0, 300000), body->GetWorldCenter(), false);

	if (body->GetLinearVelocity().y > 60) {
		body->SetLinearVelocity(b2Vec2(body->GetLinearVelocity().x, 60));
	}
}

void PlayerActionController::FlyDown()
{
	auto body = ECS::GetComponent<PhysicsBody>(EntityIdentifier::MainPlayer()).GetBody();
	body->ApplyForce(b2Vec2(0, -100000), body->GetWorldCenter(), false);

	if (body->GetLinearVelocity().y < -55) {
		body->SetLinearVelocity(b2Vec2(body->GetLinearVelocity().x, -55));
	}

}

void PlayerActionController::FlyLeft()
{
	auto body = ECS::GetComponent<PhysicsBody>(EntityIdentifier::MainPlayer()).GetBody();
	body->ApplyForce(b2Vec2(-3200000, 0), body->GetWorldCenter(), false);

	if (body->GetLinearVelocity().x < -960) {
		body->SetLinearVelocity(b2Vec2(-960, body->GetLinearVelocity().y));
	}
}

void PlayerActionController::FlyRight()
{
	auto body = ECS::GetComponent<PhysicsBody>(EntityIdentifier::MainPlayer()).GetBody();
	body->ApplyForce(b2Vec2(3200000, 0), body->GetWorldCenter(), false);

	if (body->GetLinearVelocity().x > 960) {
		body->SetLinearVelocity(b2Vec2(960, body->GetLinearVelocity().y));
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


