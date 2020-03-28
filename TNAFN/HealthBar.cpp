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
void HealthBar::createHB()
{
	unsigned int entity = ECS::CreateEntity();
	EntityIdentifier::healthBar(entity);
	ECS::AttachComponent<Sprite>(entity);
	ECS::AttachComponent<Transform>(entity);
	std::string fileName = "healthBar.png";
	ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 100, 30);
	ECS::GetComponent<Transform>(entity).SetPosition(vec3(0, 0, 100));
	unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
	ECS::SetUpIdentifier(entity, bitHolder, "realBar");
	ContactList::AddToList(entity);
}
void HealthBar::createUI1()
{
	unsigned int entity = ECS::CreateEntity();
	EntityIdentifier::ui1(entity);
	ECS::AttachComponent<Sprite>(entity);
	ECS::AttachComponent<Transform>(entity);
	std::string fileName = "ui1.png";
	ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 195, 5);
	ECS::GetComponent<Transform>(entity).SetPosition(vec3(0, 0, 100));
	unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
	ECS::SetUpIdentifier(entity, bitHolder, "UI1");
	ContactList::AddToList(entity);
}
void HealthBar::createUI2()
{
	unsigned int entity = ECS::CreateEntity();
	EntityIdentifier::ui2(entity);
	ECS::AttachComponent<Sprite>(entity);
	ECS::AttachComponent<Transform>(entity);
	std::string fileName = "ui2.png";
	ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 195, 5);
	ECS::GetComponent<Transform>(entity).SetPosition(vec3(0, 0, 100));
	unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
	ECS::SetUpIdentifier(entity, bitHolder, "UI2");
	ContactList::AddToList(entity);
}
void HealthBar::createUI3()
{
	unsigned int entity = ECS::CreateEntity();
	EntityIdentifier::ui3(entity);
	ECS::AttachComponent<Sprite>(entity);
	ECS::AttachComponent<Transform>(entity);
	std::string fileName = "ui3.png";
	ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 195, 5);
	ECS::GetComponent<Transform>(entity).SetPosition(vec3(0, 0, 100));
	unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
	ECS::SetUpIdentifier(entity, bitHolder, "UI3");
	ContactList::AddToList(entity);
}
void HealthBar::healthBarBase()
{
	unsigned int entity = EntityIdentifier::healthBar();
	Camera tempCam = ECS::GetComponent<Camera>(EntityIdentifier::MainCamera());
	ECS::GetComponent<Transform>(entity).SetPosition(vec3(tempCam.GetPositionX() - 28, tempCam.GetPositionY() + 60, 75));
	unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();

}

void HealthBar::ui1()
{
	unsigned int entity = EntityIdentifier::ui1();
	Camera tempCam = ECS::GetComponent<Camera>(EntityIdentifier::MainCamera());
	ECS::GetComponent<Transform>(entity).SetPosition(vec3(tempCam.GetPositionX() - 63, tempCam.GetPositionY() + 62, 76));
	ECS::GetComponent<Sprite>(entity).SetWidth(ECS::GetComponent<HealthBar>(EntityIdentifier::MainPlayer()).GetHealth()*195);
	unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
}

void HealthBar::ui2()
{
	unsigned int entity = EntityIdentifier::ui2();
	Camera tempCam = ECS::GetComponent<Camera>(EntityIdentifier::MainCamera());
	ECS::GetComponent<Transform>(entity).SetPosition(vec3(tempCam.GetPositionX() - 64, tempCam.GetPositionY() + 58, 77));
	ECS::GetComponent<Sprite>(entity).SetWidth(ammo * 39);
	unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();

}

void HealthBar::ui3()
{
	unsigned int entity = EntityIdentifier::ui3();
	Camera tempCam = ECS::GetComponent<Camera>(EntityIdentifier::MainCamera());
	ECS::GetComponent<Transform>(entity).SetPosition(vec3(tempCam.GetPositionX() - 68, tempCam.GetPositionY() + 54, 76));
	ECS::GetComponent<Sprite>(entity).SetWidth(power * 39);
	unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
}

void HealthBar::Damage(float dam)
{
	if (CanDamage) {
		m_health = m_health - dam;
	}
}
int HealthBar::getAmmo() const
{
	return ammo;
}
void HealthBar::checkAmmo() 
{
	if (Lammo == 2)
	{
		ammo++;
		Lammo = 0;
	}
	else
		Lammo++;

}
void HealthBar::ammoDown()
{
	ammo--;

}

void HealthBar::powerCheck()
{
	if (ECS::GetComponent<PhysicsBody>(EntityIdentifier::MainPlayer()).GetIsGrounded() == 1 && power < 5)
		power += Timer::deltaTime;
	//if (ECS::GetComponent<PhysicsBody>(EntityIdentifier::MainPlayer()).GetIsGrounded() == 0 && power > 0)
	//	power -= Timer::deltaTime;
		
}
void HealthBar::powerDown()
{
	power -= Timer::deltaTime;
}
float HealthBar::getPower()
{
	return power;
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

