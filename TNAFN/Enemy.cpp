#include "Enemy.h"
#include "Barrel.h"

void Enemy::CreateEnemy(b2World& phyworld, int x, int y, int type)
{
	//Our idel animation file
	auto Enemy_jason = File::LoadJSON("Enemy.json");
	//Creates entity
	auto entity = ECS::CreateEntity();
	//EntityIdentifier::Enemy(entity);

	//Add components
	ECS::AttachComponent<Sprite>(entity);
	ECS::AttachComponent<Transform>(entity);
	ECS::AttachComponent<AnimationController>(entity);
	ECS::AttachComponent<PhysicsBody>(entity);
	ECS::AttachComponent<AI>(entity);
	ECS::AttachComponent<HealthBar>(entity);
	ECS::AttachComponent<Barrel>(entity);
	//Sets up components
	std::string fileName = "Enemy.png";
	auto& EnemyanimController = ECS::GetComponent<AnimationController>(entity);
	EnemyanimController.InitUVs(fileName);
	//Adds first animation
	EnemyanimController.AddAnimation(Enemy_jason["Enemy_Left"]);
	EnemyanimController.AddAnimation(Enemy_jason["Enemy_Right"]);
	EnemyanimController.AddAnimation(Enemy_jason["meattack_Right"]);
	EnemyanimController.AddAnimation(Enemy_jason["meattack_Left"]);
	EnemyanimController.AddAnimation(Enemy_jason["tankwalk_Left"]);
	EnemyanimController.AddAnimation(Enemy_jason["tankwalk_Right"]);
	EnemyanimController.AddAnimation(Enemy_jason["cannonstand"]);
	if (type == 0) {
		EnemyanimController.SetActiveAnim(0);
	}
	else if (type == 1) {
		EnemyanimController.SetActiveAnim(4);
	}
	else if (type == 2) {
		EnemyanimController.SetActiveAnim(6);
	}
	ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 60, 60, true, &EnemyanimController);
	auto& tempSpr = ECS::GetComponent<Sprite>(entity);
	auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

	auto& AIController = ECS::GetComponent<AI>(entity);
	
	ECS::GetComponent<HealthBar>(entity).SetHealth(0.3f);



	//Physics body covers the entire sprite
	//ID type is player
	//Collides with Enemies and Enviroment
	//Moves
	float shrinkX = tempSpr.GetWidth() / 1.2f;
	float shrinkY = tempSpr.GetHeight() / 2.f;
	b2Body* tempBody;
	b2BodyDef tempDef;
	if (type != 2) {
		tempDef.type = b2_dynamicBody;
	}
	else {
		tempDef.type = b2_staticBody;
	}
	tempDef.position.Set(float32(x), float32(y));
	tempDef.fixedRotation = true;
	tempBody = phyworld.CreateBody(&tempDef);
	AIController = AI(entity, type);
	tempPhsBody = PhysicsBody(tempBody, float(tempSpr.GetWidth() - shrinkX), float(tempSpr.GetHeight() - shrinkY - 10),
		vec2(0.f, -5.f), true, CollisionIDs::Enemy(), CollisionIDs::Bullet() | CollisionIDs::Player() | CollisionIDs::Enemy() | CollisionIDs::Enviroment());

	tempPhsBody.SetFriction(0.15);


	if (type != 0) {
		ECS::GetComponent<Barrel>(entity).CreateBarrel(entity, x, y, ECS::GetComponent<Transform>(entity).GetPositionZ() - 1);
	}
	//fixture definition
	b2PolygonShape polygonShape;
	b2FixtureDef myFixtureDef;
	myFixtureDef.shape = &polygonShape;
	myFixtureDef.density = 10;

	//Adds a fixture the size of the body
	polygonShape.SetAsBox(14.99999f, 0.02f, b2Vec2(0.f, -15.f), 0);
	myFixtureDef.isSensor = true;
	b2Fixture* footSensorFixture = tempPhsBody.GetBody()->CreateFixture(&myFixtureDef);
	footSensorFixture->SetUserData((void*)entity);

	//Sets up thee Identifier
	unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::AnimationBit() | EntityIdentifier::AIBit()| EntityIdentifier::BarrelBit();
	ECS::SetUpIdentifier(entity, bitHolder, "Enemy");
	//ECS::SetIsEnemy(entity, true);
	
	Enemy::AddToEnemylist(entity);
	ContactList::AddToList(entity);
}

void Enemy::AddToEnemylist(unsigned int entity)
{
	EnemyList.push_back(entity);
}

void Enemy::RemoveFromEnemylist(unsigned int entity)
{
	for (int x(0); x < EnemyList.size(); x++) {
		if (EnemyList[x] == entity) {
			EnemyList.erase(EnemyList.begin() + x, EnemyList.begin() + x + 1);
			break;
		}
	}
}

bool Enemy::DeleteCheck(unsigned int entity)
{
	if (ECS::GetComponent<HealthBar>(entity).GetHealth() < 0) {
		
		ECS::GetComponent<HealthBar>(EntityIdentifier::MainPlayer()).checkAmmo();
		return true;
	}
	else {
		return false;
	}
}

void Enemy::update(entt::registry* reg)
{
	for (int x(0); x < EnemyList.size(); x++) {
		if (DeleteCheck(EnemyList[x])) {
			ContactList::RemoveFromList(EnemyList[x]);
			if (ECS::GetComponent<AI>(EnemyList[x]).getAIType() == 1|| ECS::GetComponent<AI>(EnemyList[x]).getAIType() == 2) {
				ECS::DestroyEntity(ECS::GetComponent<Barrel>(EnemyList[x]).getBarrelID());
			}
			ECS::DestroyEntity(EnemyList[x]);
			EnemyList.erase(EnemyList.begin() + x, EnemyList.begin() + x + 1);
			continue;
		}
	}
}

