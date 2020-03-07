#include "EntityIdentifier.h"

unsigned int EntityIdentifier::m_mainCamera = 0;
unsigned int EntityIdentifier::m_mainPlayer = 0;
unsigned int EntityIdentifier::m_WeaponHand = 0;
unsigned int EntityIdentifier::m_Enemy      = 0;
unsigned int EntityIdentifier::m_Bullet     = 0;
unsigned int EntityIdentifier::m_cameraBit			= 0x1;
unsigned int EntityIdentifier::m_spriteBit			= 0x10;
unsigned int EntityIdentifier::m_transformBit		= 0x100;
unsigned int EntityIdentifier::m_animationBit		= 0x1000;
unsigned int EntityIdentifier::m_linkBit			= 0x10000;
unsigned int EntityIdentifier::m_physicsBit			= 0x100000;
unsigned int EntityIdentifier::m_healthBarBit		= 0x1000000;
unsigned int EntityIdentifier::m_horiScrollCameraBit= 0x10000000;
unsigned int EntityIdentifier::m_vertScrollCameraBit= 0x2;
unsigned int EntityIdentifier::m_AIBit				= 0x20;

//(having just camera means the bit = 1)
//(having sprite, animation and transform)
//0x0111

void EntityIdentifier::AddComponent(unsigned int component)
{
	//Adds the component to the identifier
	m_identifier |= component;
}

unsigned int EntityIdentifier::MainPlayer()
{
	//Gets the main player entity number
	return m_mainPlayer;
}


bool EntityIdentifier::GetIsMainPlayer() const
{
	//Gets if this component IS attached to the main player
	return m_isMainPlayer;
}

unsigned int EntityIdentifier::WeaponHand()
{
	return m_WeaponHand;
}

bool EntityIdentifier::GetIsWeaponHand() const
{
	return m_isWeaponHand;
}

unsigned int EntityIdentifier::MainCamera()
{
	//Gets the main camera entity number
	//*There will ALWAYS be a camera, and if there isn't
	//*nothing will draw
	return m_mainCamera;
}

bool EntityIdentifier::GetIsMainCamera() const
{
	//Gets if this component IS attached to the main camera
	return m_isMainCamera;
}

unsigned int EntityIdentifier::Enemy()
{
	return m_Enemy;
}
bool EntityIdentifier::GetIsEnemy() const
{
	return m_isEnemy;
}


unsigned int EntityIdentifier::Bullet()
{
	return m_Bullet;
}

bool EntityIdentifier::GetIsBullet() const
{
	return m_isBullet;
}

unsigned int EntityIdentifier::GetEntity() const
{
	//Gets the entity number
	return m_entity;
}


unsigned int EntityIdentifier::GetIdentifier() const
{
	//Gets the identifier that holds all components
	return m_identifier;
}

std::string EntityIdentifier::GetName() const
{
	//Get the name of the entity
	return m_name;
}

bool& EntityIdentifier::GetSelected()
{
	//Gets if this is selected
	return m_selected;
}

unsigned int EntityIdentifier::CameraBit()
{
	//Gets the bit for the Camera
	return m_cameraBit;
}

unsigned int EntityIdentifier::SpriteBit()
{
	//Gets the bit for the Sprite
	return m_spriteBit;
}

unsigned int EntityIdentifier::TransformBit()
{
	//Gets the bit for the Transform
	return m_transformBit;
}

unsigned int EntityIdentifier::AnimationBit()
{
	//Gets the bit for the Animation Controller
	return m_animationBit;
}

unsigned int EntityIdentifier::LinkBit()
{
	//Gets the bit for Link
	return m_linkBit;
}

unsigned int EntityIdentifier::PhysicsBit()
{
	//Gets the bit for the Physics Body
	return m_physicsBit;
}

unsigned int EntityIdentifier::HealthBarBit()
{
	//Gets the bit for the Health Bar
	return m_healthBarBit;
}

unsigned int EntityIdentifier::HoriScrollCameraBit()
{
	return m_horiScrollCameraBit;
}

unsigned int EntityIdentifier::VertScrollCameraBit()
{
	return m_vertScrollCameraBit;
}

unsigned int EntityIdentifier::AIBit()
{
	return m_AIBit;
}

void EntityIdentifier::MainPlayer(unsigned int entity)
{
	//Sets the main player entity
	m_mainPlayer = entity;
}

void EntityIdentifier::SetIsMainPlayer(bool main)
{
	//Sets whether or not the entity that has this component, is the main player
	m_isMainPlayer = main;
}

void EntityIdentifier::WeaponHand(unsigned int entity)
{
	m_WeaponHand = entity;
}

void EntityIdentifier::SetIsWeaponHand(bool WH)
{
	m_isWeaponHand = WH;
}

void EntityIdentifier::MainCamera(unsigned int entity)
{
	//Sets the main camera entity
	m_mainCamera = entity;
}

void EntityIdentifier::SetIsMainCamera(bool main)
{
	//Sets whether or not the entity that has this component, is the main camera
	m_isMainCamera = main;
}

void EntityIdentifier::Enemy(unsigned int entity)
{
	//Sets enemy
	m_Enemy = entity;
}

void EntityIdentifier::SetIsEnemy(bool Ene)
{
	m_isEnemy = Ene;
}

void EntityIdentifier::Bullet(unsigned int entity)
{
	m_Bullet = entity;
}

void EntityIdentifier::SetIsBullet(bool Bul)
{
	m_isBullet = Bul;
}

void EntityIdentifier::SetEntity(unsigned int entity)
{
	//Sets the entity number
	m_entity = entity;
}

void EntityIdentifier::SetIdentifier(unsigned int identity)
{
	//Sets the identifier
	m_identifier = identity;
}

void EntityIdentifier::SetName(std::string name)
{
	//Set the name of the entity
	m_name = name;
}

void EntityIdentifier::SetSelected(bool selected)
{
	//Set whether the entity is selected
	m_selected = selected;
}
