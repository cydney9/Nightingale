#pragma once

#include "JSON.h"

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