#include "HealthBar.h"
#include <iostream>
#include <string>

HealthBar::HealthBar()
{
}

HealthBar::HealthBar(float health)
{
	m_health = health;
	CanDamage = true;
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
}

float HealthBar::GetHealth() const
{
	return m_health;
}

void HealthBar::SetHealth(float health)
{
	m_health = health;
}

void HealthBar::SetCanDamage(bool CanDam)
{
	CanDamage = CanDam;
}

