#ifndef __ENTITYIDENTIFIER_H__
#define __ENTITYIDENTIFIER_H__

#include "JSON.h"

class EntityIdentifier
{
public:
	//Adds the bit identifier to the whole identifier
	void AddComponent(unsigned int component);

	//Getters
	//Gets main player entity
	static unsigned int MainPlayer();
	static unsigned int healthBar();
	static unsigned int ui1();
	static unsigned int ui2();
	static unsigned int ui3();
	bool GetIsMainPlayer() const;

	//gets WeaponHand
	static unsigned int WeaponHand();
	bool GetIsWeaponHand() const;

	//Gets main camera entity
	static unsigned int MainCamera();
	bool GetIsMainCamera() const;

	//Gets Enemy
	static unsigned int Enemy();
	bool GetIsEnemy() const;

	//Gets Bullet
	static unsigned int Bullet();
	bool GetIsBullet()const;

	//Gets Bullet
	static unsigned int EBullet();
	bool GetIsEBullet()const;

	//Get entity number
	unsigned int GetEntity() const;
	//Get identifier bitfield
	unsigned int GetIdentifier() const;
	//Get Name
	std::string GetName() const;
	//Get if this entity is selected
	bool& GetSelected();
	//Gets the actual bit for the specified type
	static unsigned int CameraBit();
	static unsigned int SpriteBit();
	static unsigned int TransformBit();
	static unsigned int AnimationBit();
	static unsigned int LinkBit();
	static unsigned int PhysicsBit();
	static unsigned int HealthBarBit();
	static unsigned int HoriScrollCameraBit();
	static unsigned int VertScrollCameraBit();
	static unsigned int AIBit();
	static unsigned int BarrelBit();

	//Setters
	//Sets main player entity
	static void MainPlayer(unsigned int entity);
	//uiBar
	static void healthBar(unsigned int entity);
	static void ui1(unsigned int entity);
	static void ui2(unsigned int entity);
	static void ui3(unsigned int entity);
	void SetIsMainPlayer(bool main);

	//set WeaponHand
	static void WeaponHand(unsigned int entity);
	void SetIsWeaponHand(bool WH);

	//set Barrel
	static void Barrel(unsigned int entity);
	void SetIsBarrel(bool Bar);

	//Sets main camera entity
	static void MainCamera(unsigned int entity);
	void SetIsMainCamera(bool main);

	//Sets Enemy
	static void Enemy(unsigned int entity);
	void SetIsEnemy(bool Ene);

	//Sets Bullet
	static void Bullet(unsigned int entity);
	void SetIsBullet(bool Bul);

	//Sets Bullet
	static void EBullet(unsigned int entity);
	void SetIsEBullet(bool Bul);


	//Set entity number
	void SetEntity(unsigned int entity);
	//Set identifier bitfield
	void SetIdentifier(unsigned int identity);
	//Set the name
	void SetName(std::string name);
	//Set whether this entity is selected
	void SetSelected(bool selected);

private:
	//Main player
	static unsigned int m_mainPlayer;
	bool m_isMainPlayer = false;
	//uiBar
	static unsigned int m_healthBar;
	static unsigned int m_ui1;
	static unsigned int m_ui2;
	static unsigned int m_ui3;
	//Main camera
	static unsigned int m_mainCamera;
	bool m_isMainCamera = false;

	//WeaponHand
	static unsigned int m_WeaponHand;
	bool m_isWeaponHand = false;

	//Enemy
	static unsigned int m_Enemy;
	bool m_isEnemy = false;

	//Barrel
	static unsigned int m_Barrel;
	bool m_isBarrel = false;

	//Bullet
	static unsigned int m_Bullet;
	bool m_isBullet = false;

	//Bullet
	static unsigned int m_EBullet;
	bool m_isEBullet = false;

	//Stores the entity number
	unsigned int m_entity;
	//Stores the bit(s) of the types attached to this entity
	unsigned int m_identifier;

	//Stores the name
	std::string m_name = "";
	//Stores if this entity is selected
	bool m_selected = false;

	//Stores the bit for the specified type
	static unsigned int m_cameraBit;
	static unsigned int m_spriteBit;
	static unsigned int m_transformBit;
	static unsigned int m_animationBit;
	static unsigned int m_linkBit;
	static unsigned int m_physicsBit;
	static unsigned int m_healthBarBit;
	static unsigned int m_horiScrollCameraBit;
	static unsigned int m_vertScrollCameraBit;
	static unsigned int m_AIBit;
	static unsigned int m_BarrelBit;
};

#ifndef __ENTITYIDENTIFIERJSON_H__
#define __ENTITYIDENTIFIERJSON_H__

//Sends animation TO json file
inline void to_json(nlohmann::json& j, const EntityIdentifier& id)
{
	//Stores the identifier so that later I can know exactly what components are attached to each entity
	j["Identifier"] = id.GetIdentifier();

	//Stores whether or not this is the main camera
	j["MainCamera"] = id.GetIsMainCamera();

	//Stores whether or not this is the main player
	j["MainPlayer"] = id.GetIsMainPlayer();

	//Stores whether or not this is the enemy
	j["Enemy"] = id.GetIsEnemy();

	//Stores whether or not this is a Bullet
	j["Bullet"] = id.GetIsBullet();

	//Stores the name of this entity
	j["Name"] = id.GetName();

}

//Reads animation in FROM json file
inline void from_json(const nlohmann::json& j, EntityIdentifier& id)
{
	//Grab the identifier
	id.SetIdentifier(j["Identifier"]);

	//Grabs whether or not this is the main camera
	id.SetIsMainCamera(j["MainCamera"]);

	//Grabs whether or not this is the main player
	id.SetIsMainPlayer(j["MainPlayer"]);

	//Grabs whether or not this is the Enemy player
	id.SetIsEnemy(j["Enemy"]);

	//Grabs whether or not this is a Bullet
	id.SetIsBullet(j["Bullet"]);

	//Grabs the name of this entity
	id.SetName(j["Name"]);
}

#endif // !__ENTITYIDENTIFIERJSON_H__


#endif // !__ENTITYIDENTIFIER_H__
