#include "HealthBar.h"
#include <iostream>
#include <string>
#include "Timer.h"

HealthBar::HealthBar()
{
}

HealthBar::HealthBar(float health)
{
	m_health = health;
	CanDamage = true;
	CanBeHitByBullet = true;
}

void HealthBar::DisplayHealth()
{
	std::cout << "Health: " << std::to_string((m_health * 100.f)) << "%" << std::endl;
}

void HealthBar::Damage(float dam)
{
	if (CanDamage) {
		m_health = m_health - dam;
	}
	if (CanBeHitByBullet) {
		m_health = m_health - dam;
		CanBeHitByBullet = false;
	}
}

float HealthBar::GetHealth() const
{
	return m_health;
}

bool HealthBar::GetCanBeHitByBullet()
{
	return CanBeHitByBullet;
}

void HealthBar::SetHealth(float health)
{
	m_health = health;
}

void HealthBar::SetCanDamage(bool CanDam)
{
	CanDamage = CanDam;
}

void HealthBar::SetCanBeHitByBullet(bool CanHit)
{
	CanBeHitByBullet = CanHit;
}

void HealthBar::HitTimerUpdate()
{
	if (CanBeHitByBullet == false) {
		HitTimer -= Timer::deltaTime;
	}
	else if (HitTimer < 0) {
		HitTimer = 0.1;
		CanBeHitByBullet = true;
	}

}

