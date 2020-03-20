#include "Bullet.h"
#include<iostream>
#include<string>
#include "ContactList.h"
using namespace std;
void Bullet::CreateBullet(b2World& phyworld, float x, float y,float angle,bool Enemy)
{
	auto player_json = File::LoadJSON("Bullet.json");
	unsigned int entity = ECS::CreateEntity();
	EntityIdentifier::Bullet(entity);
	float speed;
	//Add components
	ECS::AttachComponent<Sprite>(entity);
	ECS::AttachComponent<Transform>(entity);
	ECS::AttachComponent<AnimationController>(entity);
	ECS::AttachComponent<PhysicsBody>(entity);

	std::string fileName;
	//Sets up components
	//if (Enemy) {
		fileName = "bullet.png";
	/*}
	else {
		fileName = "bullet2.png";
	}*/

	auto& animController = ECS::GetComponent<AnimationController>(entity);
	animController.InitUVs(fileName);
	ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 30, 30, true, &animController);
	//Adds first animation
	//if (Enemy) {
		animController.AddAnimation(player_json["EB_L"]);
		animController.AddAnimation(player_json["EB_R"]);
	/*}
	else {
		animController.AddAnimation(player_json["B_L"]);
		animController.AddAnimation(player_json["B_R"]);
	}*/
	auto& tempSpr = ECS::GetComponent<Sprite>(entity);
	auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);
	auto& TransformBody = ECS::GetComponent<Transform>(entity);
	//Physics body covers the entire sprite
	//ID type is player
	//Collides with Enemies and Enviroment
	//Moves
	float shrinkX = tempSpr.GetWidth() / 1.2f;
	float shrinkY = tempSpr.GetHeight() / 2.f;
	b2Body* tempBody;
	b2BodyDef tempDef;
	tempDef.type = b2_kinematicBody;
	tempDef.position.Set(float32(x), float32(y));
	tempBody = phyworld.CreateBody(&tempDef);

	//if (Enemy) {
		tempPhsBody = PhysicsBody(tempBody, float(tempSpr.GetWidth()), float(tempSpr.GetHeight()),
			vec2(0.f, 0.f), false, CollisionIDs::EBullet(), CollisionIDs::Player());
		speed = 10;
	/*}
	else {
		tempPhsBody = PhysicsBody(tempBody, float(tempSpr.GetWidth()), float(tempSpr.GetHeight()),
			vec2(0.f, 0.f), false, CollisionIDs::Bullet(), CollisionIDs::Enemy());
		speed = 100;
	}*/
	tempPhsBody.GetBody()->SetLinearVelocity(b2Vec2(speed * (cos(angle)), speed * sin(angle )));
	tempPhsBody.GetBody()->SetTransform(tempPhsBody.GetBody()->GetPosition(), angle + Transform::ToRadians(180.f));
	//Sets up thee Identifier
	unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::AnimationBit();
	ECS::SetUpIdentifier(entity, bitHolder, "Bullet");
	ECS::SetIsBullet(entity, true);
	ContactList::AddToList(entity);
	AddToBulletlist(entity);
}



void Bullet::AddToBulletlist(unsigned int entity)
{
	Bulletlist.push_back(entity);
}

void Bullet::RemoveFromBulletlist(unsigned int entity)
{
	for (int x(0); x < Bulletlist.size(); x++) {
		if (Bulletlist[x] == entity) {
			Bulletlist.erase(Bulletlist.begin() + x, Bulletlist.begin() + x + 1);
			break;
		}
	}
}

bool Bullet::DeleteCheck(unsigned int entity)
{
	auto& BulletphysicsBod = ECS::GetComponent<PhysicsBody>(entity);

	float PlayerX = ECS::GetComponent<Transform>(EntityIdentifier::MainPlayer()).GetPositionX();
	float PlayerY = ECS::GetComponent<Transform>(EntityIdentifier::MainPlayer()).GetPositionY();
	float BulletX = BulletphysicsBod.GetBody()->GetPosition().x;
	float BulletY = BulletphysicsBod.GetBody()->GetPosition().y;
	if (BulletX > PlayerX + 200 || BulletX < PlayerX - 200 || BulletY > PlayerY + 200 || BulletY < PlayerY - 200) {
		return true;
	}
	else {
		return false;
	}
}

void Bullet::update(entt::registry* reg)
{
	for (int x(0); x < Bulletlist.size(); x++) {
		if (DeleteCheck(Bulletlist[x])) {
			ContactList::RemoveFromList(Bulletlist[x]);
			ECS::DestroyEntity(Bulletlist[x]);
			Bulletlist.erase(Bulletlist.begin() + x, Bulletlist.begin() + x + 1);
			continue;
		}
	}
}
