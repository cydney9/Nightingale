#include "WeaponHand.h"
#include "ECS.h"

WeaponHand::WeaponHand(int x, int y,int z)
{
	//Our idel animation file
	auto Hand = File::LoadJSON("hand.json");

	//Creates entity
	auto entity = ECS::CreateEntity();
	EntityIdentifier::WeaponHand(entity);
	//Add components
	ECS::AttachComponent<Sprite>(entity);
	ECS::AttachComponent<Transform>(entity);
	ECS::AttachComponent<AnimationController>(entity);

	//Sets up components
	std::string fileName = "WeaponHand.png";
	auto& animController = ECS::GetComponent<AnimationController>(entity);
	animController.InitUVs(fileName);

	//Adds first animation
	animController.AddAnimation(Hand["HandRight"]);
	animController.AddAnimation(Hand["HandLeft"]);
	animController.AddAnimation(Hand["Attacking"]);
	ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 55, 35, true, &animController);

	ECS::GetComponent<Transform>(entity).SetPosition(vec3(x,y,z));

	//Sets up thee Identifier
	unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::AnimationBit();
	ECS::SetUpIdentifier(entity, bitHolder, "weaponHand");
}

void WeaponHand::Update()
{
	auto PlayerPos = ECS::GetComponent<Transform>(EntityIdentifier::MainPlayer()).GetPosition();
	this->SetPosition(PlayerPos);
	Transform::Update();
}
