#include "HelloWorld.h"

b2Vec2 WallPos[] = { b2Vec2(-750, 330),
b2Vec2(-360 , 329),
b2Vec2(-330 , 360),
b2Vec2(-180 , 360),
b2Vec2(-120 , 420), //1
b2Vec2(-0 , 420),
b2Vec2(29,  390),
b2Vec2(60,  390),
b2Vec2(89,  359),
b2Vec2(119, 359),
b2Vec2(148, 330),
b2Vec2(299, 330),
b2Vec2(299, 389),
b2Vec2(269, 390),
b2Vec2(270, 420),
b2Vec2(299, 421),
b2Vec2(299, 480),
b2Vec2(449, 479),
b2Vec2(449, 451),
b2Vec2(330, 449),
b2Vec2(329, 330),
b2Vec2(569, 330),
b2Vec2(599, 300),
b2Vec2(599, 0),
b2Vec2(569, 0),
b2Vec2(509, 60),
b2Vec2(480, 59),
b2Vec2(450, 89),
b2Vec2(389, 90),
b2Vec2(359, 119),
b2Vec2(299, 120),
b2Vec2(270, 90),
b2Vec2(239, 90),
b2Vec2(209, 60),
b2Vec2(-150, 59),
b2Vec2(-209, 0),
b2Vec2(-269, 0),
b2Vec2(-300, -29),
b2Vec2(-360, -30),
b2Vec2(-450, -119),
b2Vec2(-540, -120),
b2Vec2(-570, -149),
b2Vec2(-600, -149),
b2Vec2(-630, -179),
b2Vec2(-630, -389),
b2Vec2(-570, -449),
b2Vec2(-570, -479),
b2Vec2(-509, -479),
b2Vec2(-480, -449),
b2Vec2(-389, -449),
b2Vec2(-361, -479),
b2Vec2(-181, -479),
b2Vec2(-150, -449),
b2Vec2(-150, -390),
b2Vec2(-300, -389),
b2Vec2(-299, -359),
b2Vec2(-90, -359),
b2Vec2(-90, -330),
b2Vec2(-58, -298),
b2Vec2(-30, -299),
b2Vec2(-0, -329),
b2Vec2(-0, -389),
b2Vec2(-30, -419),
b2Vec2(-29, -449),
b2Vec2(89, -449),
b2Vec2(89.5, -479),
b2Vec2(-29., -479),
b2Vec2(30.0, -539),
b2Vec2(210., -539),
b2Vec2(209., -569),
b2Vec2(29.6, -569),
b2Vec2(89.4, -629),
b2Vec2(119., -629),
b2Vec2(150., -659),
b2Vec2(329., -658),
b2Vec2(359., -629),
b2Vec2(509., -629),
b2Vec2(599., -539),
b2Vec2(599., -449),
b2Vec2(569., -419),
b2Vec2(509., -419),
b2Vec2(418., -330),
b2Vec2(238., -329),
b2Vec2(210., -300),
b2Vec2(28.4, -299),
b2Vec2(-0.5, -270),
b2Vec2(-61., -269),
b2Vec2(-149, -180),
b2Vec2(-210, -179),
b2Vec2(-240, -209),
b2Vec2(-300, -209),
b2Vec2(-331 , -239),
b2Vec2(-419 , -239),
b2Vec2(-450 , -268),
b2Vec2(-510 , -267),
b2Vec2(-510 , -239),
b2Vec2(-480 , -209),
b2Vec2(-390 , -209),
b2Vec2(-360 , -180),
b2Vec2(-300 , -180),
b2Vec2(-241 , -120),
b2Vec2(-210 , -119),
b2Vec2(-150 , -60),
b2Vec2(-120 , -60),
b2Vec2(-90 , -30),
b2Vec2(359, -29),
b2Vec2(359, -59),
b2Vec2(149, -59),
b2Vec2(149, -89),
b2Vec2(209, -149),
b2Vec2(599, -149),
b2Vec2(660, -90),
b2Vec2(659, 300),
b2Vec2(690, 330),
b2Vec2(749, 330),
b2Vec2(749, 539),
b2Vec2(509, 539),
b2Vec2(509, 420),
b2Vec2(539, 419),
b2Vec2(539, 391),
b2Vec2(360, 390),
b2Vec2(359, 420),
b2Vec2(479, 420),
b2Vec2(479, 540),
b2Vec2(209, 540),
b2Vec2(209, 570),
b2Vec2(239, 600),
b2Vec2(749, 600),
b2Vec2(749, 750),
b2Vec2(-750, 750),
b2Vec2(-749, 334) };


HelloWorld::HelloWorld(std::string name)
	:Scene (name)
{
	m_gravity = b2Vec2(float32(0.f), float32(-9.8));
	m_physicsWorld->SetGravity(m_gravity);
	m_physicsWorld->SetContactListener(&listener);
}

void HelloWorld::InitScene(float windowWidth, float windowHeight)
{
	//Dynamically allocates the register (so when you unload the scene when you switch you switch between scenes
	//you can later reInt this scene
	m_sceneReg = new entt::registry;

	//Attch the register
	ECS::AttachRegister(m_sceneReg);

	//Set up aspect ratio for the camera
	float aspectRatio = windowWidth / windowHeight;

	//Setup Main Camera entity
	{
		//Creates Camera entity
		auto entity = ECS::CreateEntity();
		EntityIdentifier::MainCamera(entity);

		//Creates new orthougraphic camera
		ECS::AttachComponent<Camera>(entity);
		ECS::AttachComponent<HorizontalScroll>(entity);
		ECS::AttachComponent<VerticalScroll>(entity);

		vec4 temp = ECS::GetComponent<Camera>(entity).GetOrthoSize();
		ECS::GetComponent<Camera>(entity).SetWindowSize(vec2(float(windowWidth), float(windowHeight)));
		ECS::GetComponent<Camera>(entity).Orthographic(aspectRatio, temp.x, temp.y, temp.z, temp.w, -100.f, 100.f);
		ECS::GetComponent<Camera>(entity).Zoom(20);
		ECS::GetComponent<Camera>(entity).SetPosition(vec3(ECS::GetComponent<Camera>(entity).GetPositionX(), ECS::GetComponent<Camera>(entity).GetPositionY()-20, ECS::GetComponent<Camera>(entity).GetPositionZ()));

		ECS::GetComponent<HorizontalScroll>(entity).SetCam(&ECS::GetComponent<Camera>(entity));
		ECS::GetComponent<HorizontalScroll>(entity).SetOffset(10.f);

		ECS::GetComponent<VerticalScroll>(entity).SetCam(&ECS::GetComponent<Camera>(entity));
		ECS::GetComponent<VerticalScroll>(entity).SetOffset(0.f);

		//Sets up the Indentifier
		unsigned int bitHolder = EntityIdentifier::HoriScrollCameraBit()| EntityIdentifier::VertScrollCameraBit() | EntityIdentifier::CameraBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Horizontal & Vertical Scrolling Cam");
		ECS::SetIsMainCamera(entity, true);
		

	}

	//Setup new Entity{
	//{
		//Creates entity
		//auto entity = ECS::CreateEntity();

		//Creates new orthographic camera
		//ECS::AttachComponent<HealthBar>(entity);
		//ECS::GetComponent<HealthBar>(entity).SetHealth(0.7f);

		//Sets up the Identifier
		//unsigned int bitHolder = EntityIdentifier::HealthBarBit();
		//ECS::SetUpIdentifier(entity, bitHolder, "HealthBar Entity");
	//}
	
	HealthBar::createHB();
	HealthBar::createUI1();
	HealthBar::createUI2();
	HealthBar::createUI3();

//	Setup Player Entity
	Player::CreatePlayer(*m_physicsWorld, -730, 350);

	//weaponhand
	WeaponHand H(ECS::GetComponent<PhysicsBody>(EntityIdentifier::MainPlayer()).GetPosition().x, ECS::GetComponent<PhysicsBody>(EntityIdentifier::MainPlayer()).GetPosition().y, ECS::GetComponent<Transform>(EntityIdentifier::MainPlayer()).GetPosition().z - 1);

	//	Setup Enemy Entity
	Enemy::CreateEnemy(*m_physicsWorld, -323, 376, 0);

	Enemy::CreateEnemy(*m_physicsWorld, -26, 433, 1);

	Enemy::CreateEnemy(*m_physicsWorld, 284, 438, 2);

	Enemy::CreateEnemy(*m_physicsWorld, 314, 496, 2);

	Enemy::CreateEnemy(*m_physicsWorld, 540, 353, 0);

	Enemy::CreateEnemy(*m_physicsWorld, 344, -13, 2);

	Enemy::CreateEnemy(*m_physicsWorld, 237, -109, 1);
	Enemy::CreateEnemy(*m_physicsWorld, -130, -28, 0);
	Enemy::CreateEnemy(*m_physicsWorld, -284, -344, 2);

	Enemy::CreateEnemy(*m_physicsWorld, 178, -640, 1);
	Enemy::CreateEnemy(*m_physicsWorld, 255, -640, 1);
	Enemy::CreateEnemy(*m_physicsWorld, 306, -640, 1);
	//Set up ground
	{
		//Creates new entity
		auto entity = ECS::CreateEntity();
		//Attaches Sprite and Transform Components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);

		//Loads in the second big Sprite Sheet
		std::string fileName = "Map1.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 1500, 1500);
		//Gets the transform component and sets the position to middle of the screen
		//(Undernearh everything so that it acts as a backgroung)
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(0.f, 0.f, -10.f));

		//Grabs reference to various components
		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		//create body
		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_staticBody;
		tempDef.position.Set(float32(0.f), float32(0.f));
		tempDef.fixedRotation = true;
		tempBody = m_physicsWorld->CreateBody(&tempDef);
		tempPhsBody = PhysicsBody(tempBody ,&WallPos[0],131,false,  CollisionIDs::Enviroment(), CollisionIDs::Enemy()| CollisionIDs::Player());
		tempPhsBody.SetFriction(0.8);
		//Sets up the identifier
		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::PhysicsBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Ground");

	}
	




	//Set up background
	{
		//Creates new entity
		auto entity = ECS::CreateEntity();
		//Attaches Sprite and Transform Components
		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);

		//Sets up components
		std::string fileName = "Background.jpg";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 600, 400);

		ECS::GetComponent<Transform>(entity).SetPosition(vec3(0.f, 0.f, -11.f));

		//Sets up thee Identifier
		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Sky");
	}

	//Make the camera focus on the main player
		//we do this at very bottom so we get the most accurate pointer to our Transform
	ECS::GetComponent<HorizontalScroll>(EntityIdentifier::MainCamera()).SetFocus(&ECS::GetComponent<Transform>(EntityIdentifier::MainPlayer()));
	ECS::GetComponent<VerticalScroll>(EntityIdentifier::MainCamera()).SetFocus(&ECS::GetComponent<Transform>(EntityIdentifier::MainPlayer()));
}
