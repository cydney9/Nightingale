#include "Barrel.h"
#include "ECS.h"
void Barrel::CreateBarrel(unsigned int entity, int x, int y, int z)
{
	LinkedEntity = entity;
	//Our idel animation file
	auto Barrel = File::LoadJSON("Barrel.json");
	//Creates entity
	auto Bentity = ECS::CreateEntity();
	EntityIdentifier::Barrel(Bentity);
	//Add components
	ECS::AttachComponent<Sprite>(Bentity);
	ECS::AttachComponent<Transform>(Bentity);
	ECS::AttachComponent<AnimationController>(Bentity);

	//Sets up components
	std::string fileName = "gun.png";
	auto& animController = ECS::GetComponent<AnimationController>(Bentity);
	animController.InitUVs(fileName);

	//Adds first animation
	animController.AddAnimation(Barrel["Barrel_Left"]);
	ECS::GetComponent<Sprite>(Bentity).LoadSprite(fileName, 55, 35, true, &animController);

	ECS::GetComponent<Transform>(Bentity).SetPosition(vec3(x, y, ECS::GetComponent<Transform>(entity).GetPosition().z - 1));

	//Sets up thee Identifier
	unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::AnimationBit();
	ECS::SetUpIdentifier(Bentity, bitHolder, "Barrel");

	BarrelID = Bentity;
}

void Barrel::Update(int AI)
{
	float x = ECS::GetComponent<Transform>(LinkedEntity).GetPosition().x;
	float y = ECS::GetComponent<Transform>(LinkedEntity).GetPosition().y;
	float z = ECS::GetComponent<Transform>(LinkedEntity).GetPosition().z;

	float PlayerX = ECS::GetComponent<Transform>(EntityIdentifier::MainPlayer()).GetPosition().x;
	float PlayerY = ECS::GetComponent<Transform>(EntityIdentifier::MainPlayer()).GetPosition().y;
	ECS::GetComponent<Transform>(BarrelID).SetPosition(vec3(x, y, z - 1));

	float dx = x - PlayerX;
	float dy = y - PlayerY;


	playerDir = atan2(dy, dx);
	playerDir = playerDir + Transform::ToRadians(180.f);
	if (AI == 1) {
		if (PlayerX > x) {
			if (playerDir >= 0.5235987756 && playerDir <= 3.1415926536) {
				playerDir = 0.5235987756;
			}
			else if (playerDir >= 3.1415926536 && playerDir <= 5.7595865316) {
				playerDir = 5.7595865316;
			}
		}
		else if (PlayerX < x) {

			if (playerDir <= 2.617993878 && playerDir >= 0) {
				playerDir = 2.617993878;
			}
			else if (playerDir >= 3.6651914292 && playerDir <= 6.2831853072) {
				playerDir = 3.6651914292;
			}
		}
	}
	ECS::GetComponent<Transform>(BarrelID).SetRotationAngleZ(playerDir);

}

int Barrel::getBarrelID()
{
	return BarrelID;
}

float Barrel::getAngle()
{
	return playerDir;
}
