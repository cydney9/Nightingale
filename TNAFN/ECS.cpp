#include "ECS.h"

entt::registry* ECS::m_reg = nullptr;

void ECS::AttachRegister(entt::registry * reg)
{
	//Attach reference to the registry
	m_reg = reg;
}

void ECS::UnattachRegister()
{
	//Unattaches the register
	m_reg = nullptr;
}

unsigned ECS::CreateEntity()
{
	//create the entity
	auto entity = m_reg->create();

	//Attach Entity Identifier to the entity
	m_reg->assign<EntityIdentifier>(entity);

	//Return entity ID
	return entity;
}

void ECS::DestroyEntity(unsigned entity)
{
	if (m_reg->has<PhysicsBody>(entity)) {
		m_reg->get<PhysicsBody>(entity).deleteBody();
	}
	//Destroys the entity
	m_reg->destroy(entity);
}

void ECS::SetUpIdentifier(unsigned entity, unsigned componentID, std::string name)
{
	//Gets reference to the component
	auto& id = GetComponent<EntityIdentifier>(entity);
	//Set the entity
	id.SetEntity(entity);
	//Set the entity identifier unsigned int
	id.AddComponent(componentID);
	//Set the name of the entity
	id.SetName(name);
}

void ECS::SetIsMainCamera(unsigned entity, bool mainCamera)
{
	//Gets reference to the component
	auto& id = GetComponent<EntityIdentifier>(entity);
	//Sets main camera entity
	EntityIdentifier::MainCamera(entity);
	//Sets whether this entity is the main camera
	id.SetIsMainCamera(mainCamera);
}

void ECS::SetIsMainPlayer(unsigned entity, bool mainPlayer)
{
	//Gets reference to the component
	auto& id = GetComponent<EntityIdentifier>(entity);
	//Sets main player entity
	EntityIdentifier::MainPlayer(entity);
	//Sets whether this entity is the main player
	id.SetIsMainPlayer(mainPlayer);
}

void ECS::SetIsWeaponHand(unsigned entity, bool WeaponHand)
{
	//Gets reference to the component
	auto& id = GetComponent<EntityIdentifier>(entity);
	//Sets WeaponHand entity
	EntityIdentifier::WeaponHand(entity);
	//Sets whether this entity is the WeaponHand
	id.SetIsWeaponHand(WeaponHand);
}

void ECS::SetIsEnemy(unsigned entity, bool Enemy)
{
	//Gets reference to the component
	auto& id = GetComponent<EntityIdentifier>(entity);
	//Sets Enemy entity
	EntityIdentifier::Enemy(entity);
	//Sets whether this entity is the Enemy
	id.SetIsEnemy(Enemy);
}

void ECS::SetIsBullet(unsigned entity, bool Bullet)
{
	//Gets reference to the component
	auto& id = GetComponent<EntityIdentifier>(entity);
	//Sets Bullet entity
	EntityIdentifier::Bullet(entity);
	//Sets whether this entity is the Bullet
	id.SetIsBullet(Bullet);
}


void ECS::SetIsEBullet(unsigned entity, bool Bullet)
{
	//Gets reference to the component
	auto& id = GetComponent<EntityIdentifier>(entity);
	//Sets Bullet entity
	EntityIdentifier::EBullet(entity);
	//Sets whether this entity is the Bullet
	id.SetIsEBullet(Bullet);
}