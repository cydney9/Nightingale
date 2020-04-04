#pragma once

#include "JSON.h"
#include "ECS.h"
#include "ContactList.h"
static bool CanBeHitByBullet=true;
class HealthBar
{
	friend class PlayerActionController;
public:
	//Creates the health bar
	HealthBar();
	//Creates the health bar with this amount of health
	HealthBar(float health);
	//Destorys the current health
	void DisplayHealth();
	static void createHB();
	static void createUI1();
	static void createUI2();
	static void createUI3();
	void healthBarBase();

	//3am;
	void ui1();
	void ui2();
	void ui3();
	int getAmmo()const;
	void checkAmmo();
	void ammoDown();
	void DD();
	void powerCheck();
	float getPower();
	void powerDown();

	void Damage(float dam);
	//Getters
	float GetHealth() const;
	bool GetCanBeHitByBullet();
	//Setters
	void SetHealth(float health);
	void SetCanDamage(bool CanDam);
	void SetCanBeHitByBullet(bool CanHit);

	//Timer
	void HitTimerUpdate();
private:
	//100%health
	int ammo = 5;
	unsigned int Lammo = 0;
	 float power = 5.f;
	float m_health = 1.f;

	float HitTimer = 0.1;
	bool CanBeHitByBullet ;
	bool CanDamage;
};

//Sends healthbar To json file
inline void to_json(nlohmann::json& j, const HealthBar& bar) {
	j["Health"] = bar.GetHealth();
}

//Sends healthbar from json file
inline void from_json(const nlohmann::json& j, HealthBar& bar) {
	bar.SetHealth(j["Health"]);
}