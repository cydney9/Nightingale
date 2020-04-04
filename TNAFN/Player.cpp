#include "Player.h"
#include <GPCSound.h>

void Player::CreatePlayer(b2World& phyworld, int x, int y)
{
	auto player_json = File::LoadJSON("player.json");
	unsigned int entity = ECS::CreateEntity();
	EntityIdentifier::MainPlayer(entity);

	//Add components
	ECS::AttachComponent<Sprite>(entity);
	ECS::AttachComponent<Transform>(entity);
	ECS::AttachComponent<AnimationController>(entity);
	ECS::AttachComponent<PhysicsBody>(entity);
	ECS::AttachComponent<HealthBar>(entity);

	//Sets up components
	std::string fileName = "player.png";
	auto& animController = ECS::GetComponent<AnimationController>(entity);
	animController.InitUVs(fileName);
	ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 60, 60, true, &animController);
	//Adds first animation
	animController.AddAnimation(player_json["standRight"]);
	animController.AddAnimation(player_json["standLeft"]);

	animController.AddAnimation(player_json["walkRight"]);
	animController.AddAnimation(player_json["walkLeft"]);

	animController.AddAnimation(player_json["flyRight"]);
	animController.AddAnimation(player_json["flyLeft"]);

	animController.AddAnimation(player_json["dashRight"]);
	animController.AddAnimation(player_json["dashLeft"]);

	animController.AddAnimation(player_json["attackRight1"]);
	animController.AddAnimation(player_json["attackLeft1"]);

	animController.AddAnimation(player_json["attackRight2"]);
	animController.AddAnimation(player_json["attackLeft2"]);

	animController.AddAnimation(player_json["attackRight3"]);
	animController.AddAnimation(player_json["attackLeft3"]);

	animController.AddAnimation(player_json["dashRight"]);
	animController.AddAnimation(player_json["dashLeft"]);
	auto& tempSpr = ECS::GetComponent<Sprite>(entity);
	auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);
	//Physics body covers the entire sprite
	//ID type is player
	//Collides with Enemies and Enviroment
	//Moves
	float shrinkX = tempSpr.GetWidth() /1.2f;
	float shrinkY = tempSpr.GetHeight() / 2.f;
	b2Body* tempBody;
	b2BodyDef tempDef;
	tempDef.type = b2_dynamicBody;
	tempDef.position.Set(float32(x), float32(y));
	tempDef.fixedRotation = true;
	tempBody = phyworld.CreateBody(&tempDef);

	tempPhsBody = PhysicsBody(tempBody, float(tempSpr.GetWidth() - shrinkX), float(tempSpr.GetHeight()- shrinkY - 10),
	vec2(0.f, -5.f), true, CollisionIDs::Player(), CollisionIDs::EBullet()|CollisionIDs::Enemy()| CollisionIDs::Enviroment());
	tempPhsBody.SetFriction(0.15);

	//fixture definition
	b2PolygonShape polygonShape;
	b2FixtureDef myFixtureDef;
	myFixtureDef.shape = &polygonShape;
	myFixtureDef.density = 10;

	//Adds a fixture the size of the body
	polygonShape.SetAsBox(5.f, 0.52f, b2Vec2(0.f, -14.5f), 0);
	myFixtureDef.isSensor = true;
	b2Fixture* footSensorFixture = tempPhsBody.GetBody()->CreateFixture(&myFixtureDef);
	footSensorFixture->SetUserData((void*)entity);

	//Sets up thee Identifier
	unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::AnimationBit()| EntityIdentifier::HealthBarBit()| CollisionIDs::EBullet();
	ECS::SetUpIdentifier(entity, bitHolder, "Player");
	ECS::SetIsMainPlayer(entity, true);

	ContactList::AddToList(entity);
}
