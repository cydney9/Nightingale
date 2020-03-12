#include "Enemy.h"

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
	//Sets up components
	std::string fileName = "Enemy.png";
	auto& EnemyanimController = ECS::GetComponent<AnimationController>(entity);
	EnemyanimController.InitUVs(fileName);
	//Adds first animation
	EnemyanimController.AddAnimation(Enemy_jason["Enemy_Left"]);
	EnemyanimController.AddAnimation(Enemy_jason["Enemy_Right"]);
	EnemyanimController.SetActiveAnim(0);
	ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 30, 30, true, &EnemyanimController);
	auto& tempSpr = ECS::GetComponent<Sprite>(entity);
	auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

	auto& AIController = ECS::GetComponent<AI>(entity);

	//Physics body covers the entire sprite
	//ID type is player
	//Collides with Enemies and Enviroment
	//Moves
	float shrinkX = tempSpr.GetWidth() / 1.7f;
	float shrinkY = tempSpr.GetWidth() / 2.f;
	b2Body* tempBody;
	b2BodyDef tempDef;
	tempDef.type = b2_dynamicBody;
	tempDef.position.Set(float32(x), float32(y));
	tempDef.fixedRotation = true;
	tempBody = phyworld.CreateBody(&tempDef);
	tempPhsBody = PhysicsBody(tempBody, float(tempSpr.GetWidth() - shrinkX), float(tempSpr.GetHeight() - 10),
		vec2(0.f, -5.f), true, CollisionIDs::Enemy(), CollisionIDs::Bullet()| CollisionIDs::Player()| CollisionIDs::Enemy()| CollisionIDs::Enviroment());
	tempPhsBody.SetFriction(0.15);

	AIController = AI(entity, type);

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
	unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::AnimationBit() | EntityIdentifier::AIBit();
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
	/*auto& BulletphysicsBod = ECS::GetComponent<PhysicsBody>(entity);

	float PlayerX = ECS::GetComponent<Transform>(EntityIdentifier::MainPlayer()).GetPositionX();
	float PlayerY = ECS::GetComponent<Transform>(EntityIdentifier::MainPlayer()).GetPositionY();
	float BulletX = BulletphysicsBod.GetBody()->GetPosition().x;
	float BulletY = BulletphysicsBod.GetBody()->GetPosition().y;
	if (BulletX > PlayerX + 200 || BulletX < PlayerX - 200 || BulletY > PlayerY + 200 || BulletY < PlayerY - 200) {
		return true;
	}
	else {
		return false;
	}*/

	return false;
}

void Enemy::update(entt::registry* reg)
{
	for (int x(0); x < EnemyList.size(); x++) {
		if (DeleteCheck(EnemyList[x])) {
			ContactList::RemoveFromList(EnemyList[x]);
			ECS::DestroyEntity(EnemyList[x]);
			EnemyList.erase(EnemyList.begin() + x, EnemyList.begin() + x + 1);
			continue;
		}
	}
}


