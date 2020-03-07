#include "Game.h"
#include <random>
#include "Utilities.h"
#include "Scene.h"
#include "vector"
#include "GPCSound.h"

#include <chrono>
#include <ctime>
#include "PlayerActionController.h"



//value use for combo
bool IsCombo=false;
static std::vector<string> ComboBuffer;




int ClickCounter = 0;

vector<vec2> point;

bool IsFlying = false;

//Left(-1) or Right(1)
int LOR = -1;

int AnimNum = 0;

float handangle = 0;



Game::~Game()
{
	//If window isn't equal to nullptr
	if (m_window != nullptr)
	{
		//Delete window
		delete m_window;
		//set window to nullptr
		m_window = nullptr;
	}

	//Goes through the scenes and deletes them
	for (unsigned i = 0; i < m_scenes.size(); i++)
	{
		if (m_scenes[i] != nullptr)
		{
			delete m_scenes[i];
			m_scenes[i] = nullptr;
		}
	}
}

void Game::InitGame()
{
	//Scene names and clear colors
	m_name = "Hello World";
	m_clearColor = vec4(0.15f, 0.33f, 0.58f, 1.f);

	//Initializes the backend
	BackEnd::InitBackEnd(m_name);

	//Grabs the initialized window
	m_window = BackEnd::GetWindow();



	//Creates a new HelloWorld scene
	m_scenes.push_back(new HelloWorld("HorizontalScrolling"));
	m_scenes.push_back(new Scene("First Loaded Scene"));
	m_scenes.push_back(new HelloWorld("second Loaded Scene"));
	m_scenes.push_back(new HelloWorld("third Loaded Scene"));
	//Sets active scene reference to our HelloWorld scene
	m_activeScene = m_scenes[0];


	m_activeScene->InitScene(float(BackEnd::GetWindowWidth()), float(BackEnd::GetWindowHeight()));
	//*m_activeScene = File::LoadJSON("HorizontalScrolling.json");
	//Set m_register to point to the register in the active scene
	m_register = m_activeScene->GetScene();

	PhysicsSystem::Init();
}

bool Game::Run()
{
	SoundManager::init("./Assets/Sounds/");
	Sound2D _test("Sound.wav", "group1");
	//While window is still open
	while (m_window->isOpen())
	{

		std::vector<Sound2D> sound;
		if (!_test.isPlaying())
				_test.play();

		frameStart = SDL_GetTicks();

		//Clear window with clearColor
		m_window->Clear(m_clearColor);
		//Updates the game
		Update();
		//Draws the game
		BackEnd::Draw(m_register);

		//Draws ImGUI
		if (m_guiActive)
			GUI();
		
		//Flips the windows
		m_window->Flip();
		
		//Polls events and then checks them
		BackEnd::PollEvents(m_register, &m_close, &m_motion, &m_click, &m_wheel);
		CheckEvents();

		//does the window have keyboard focus?
		if (Input::m_windowFocus)
		{
			//Accept all input
			AcceptInput();
		}

		frameTime = SDL_GetTicks() - frameStart;

		if (frameDelay > frameTime) {
			SDL_Delay(frameDelay - frameTime);
		}

	}

	return true;
}

void Game::Update()
{
	//Update timer
	Timer::Update();
	//Update the backend
	BackEnd::Update(m_register);

	//Update Physics System
	PhysicsSystem::Update(m_register, m_activeScene->GetPhysicsWorld());
}

void Game::GUI()
{
	UI::Start(BackEnd::GetWindowWidth(), BackEnd::GetWindowHeight());

	ImGui::Text("Place your different tabs below.");

	if (ImGui::BeginTabBar(""))
	{
		BackEnd::GUI(m_register, m_activeScene);

		ImGui::EndTabBar();
	}

	UI::End();
}

void Game::CheckEvents()
{
	if (m_close)
		m_window->Close();

	MouseMotion(BackEnd::GetMotionEvent());

	if (m_click)
		MouseClick(BackEnd::GetClickEvent());

	if (m_wheel)
		MouseWheel(BackEnd::GetWheelEvent());
}

void Game::AcceptInput()
{
	XInputManager::Update();
	//Just calls all the other input functions 
	KeyboardDown();
	KeyboardHold();
	KeyboardUp();
	auto bodyX = ECS::GetComponent<Transform>(EntityIdentifier::MainPlayer()).GetPositionX();
	auto bodyY = ECS::GetComponent<Transform>(EntityIdentifier::MainPlayer()).GetPositionY();


	if (ECS::GetComponent<PhysicsBody>(EntityIdentifier::MainPlayer()).GetIsGrounded()) {
		cout << "is grounded" << endl;
	}

	ECS::GetComponent<Transform>(EntityIdentifier::WeaponHand()).SetPosition(vec3(bodyX + (1.8f*LOR) , bodyY - 3.0f, ECS::GetComponent<Transform>(EntityIdentifier::MainPlayer()).GetPosition().z - 1));

	//Resets the key flags
	//Must be done once per frame for input to work
	Input::ResetKeys();
}

void Game::GamepadInput()
{
	XInputController* tempCon;
	//Gamepad button stroked (pressed)
	for (int i = 0; i < 3; i++)
	{
		if (XInputManager::ControllerConnected(i))
		{
			tempCon = XInputManager::GetController(i);
			tempCon->SetStickDeadZone(0.1f);

 			//If the controller is connected, we run the different input types
			GamepadStroke(tempCon);
			GamepadUp(tempCon);
			GamepadDown(tempCon);
			GamepadStick(tempCon);
			GamepadTrigger(tempCon);
		}
	}
}

void Game::GamepadStroke(XInputController* con)
{
	m_activeScene->GamepadStroke(con);
}

void Game::GamepadUp(XInputController* con)
{
	m_activeScene->GamepadUp(con);
}

void Game::GamepadDown(XInputController* con)
{
	m_activeScene->GamepadDown(con);
}

void Game::GamepadStick(XInputController* con)
{
	m_activeScene->GamepadStick(con);
}

void Game::GamepadTrigger(XInputController* con)
{
	m_activeScene->GamepadTrigger(con);
}

void Game::KeyboardHold()
{
	auto body = ECS::GetComponent<PhysicsBody>(EntityIdentifier::MainPlayer()).GetBody();
	auto PlayerAnim = ECS::GetComponent<AnimationController>(EntityIdentifier::MainPlayer());
	//Keyboard button held

	b2Vec2 vel = b2Vec2(body->GetLinearVelocity());
	float desireVel = body->GetLinearVelocity().x;

	if (Input::GetKey(Key::A) && IsFlying == false) {
		PlayerActionController::walkLeft();
	}
	if (Input::GetKey(Key::D) && IsFlying == false) {
		PlayerActionController::walkRight();
	}


	/*
	if (Input::GetKey(Key::A) && IsFlying == false) {
		body->SetLinearVelocity(b2Vec2(-40, body->GetLinearVelocity().y));
	}
	if (Input::GetKey(Key::D) && IsFlying == false) {
		body->SetLinearVelocity(b2Vec2(40, body->GetLinearVelocity().y));
	}

	if (Input::GetKey(Key::W) && IsFlying == false) {
		body->SetLinearVelocity(b2Vec2(body->GetLinearVelocity().x, 40));
	}
	if (Input::GetKey(Key::S) && IsFlying == false) {
		body->SetLinearVelocity(b2Vec2(body->GetLinearVelocity().x, -40));
	}
	*/


	//Flying mode

	if (Input::GetKey(Key::Space)&&IsFlying == true) {
		if (Input::GetKey(Key::W)) {
			PlayerActionController::FlyUp();
		}		
		if (Input::GetKey(Key::S)) {
			PlayerActionController::FlyDown();
		}		
		if (Input::GetKey(Key::A)) {
			PlayerActionController::FlyLeft();
		}		
		if (Input::GetKey(Key::D)) {
			PlayerActionController::FlyRight();
		}

	}

	if (Input::GetKey(Key::O)) {    //zoom in
		m_register->get<Camera>(EntityIdentifier::MainCamera()).Zoom(1);
	}
	if (Input::GetKey(Key::P)) {    //zoom out
		m_register->get<Camera>(EntityIdentifier::MainCamera()).Zoom(-1);
	}

}

void Game::KeyboardDown()
{

	//Keyboard button down
	m_activeScene->KeyboardDown();
	if (Input::GetKeyDown(Key::F4)) {
		printf("F4 Key Down\n");
	}


	auto body = ECS::GetComponent<PhysicsBody>(EntityIdentifier::MainPlayer()).GetBody();
	b2Vec2 LinearVelocity = b2Vec2(body->GetLinearVelocity());
	if (Input::GetKeyDown(Key::Space)&& ECS::GetComponent<PhysicsBody>(EntityIdentifier::MainPlayer()).GetIsGrounded()==true) {
		body->ApplyForce(b2Vec2(0, 9600000), body->GetWorldCenter(), true);

	}else if (Input::GetKeyDown(Key::Space) && ECS::GetComponent<PhysicsBody>(EntityIdentifier::MainPlayer()).GetIsGrounded() == false) {
		body->SetGravityScale(0.05);
		IsFlying = true;
	}
	if (Input::GetKeyDown(Key::Shift)) {
		body->ApplyLinearImpulse(b2Vec2(10000000000000000000, 0), body->GetWorldCenter(), true);
	}


}

void Game::KeyboardUp()
{
	auto body = ECS::GetComponent<PhysicsBody>(EntityIdentifier::MainPlayer()).GetBody();
	/*
	if (Input::GetKeyUp(Key::A) && IsFlying == false) {
		body->SetLinearVelocity(b2Vec2(0, 0));
	}
	if (Input::GetKeyUp(Key::D) && IsFlying == false) {
		body->SetLinearVelocity(b2Vec2(0, 0));
	}

	if (Input::GetKeyUp(Key::W) && IsFlying == false) {
		body->SetLinearVelocity(b2Vec2(0, 0));
	}
	if (Input::GetKeyUp(Key::S) && IsFlying == false) {
		body->SetLinearVelocity(b2Vec2(0, 0));
	}
	*/
	//Keyboard button up
	m_activeScene->KeyboardUp();

	if (Input::GetKeyUp(Key::F1))
	{
		if (!UI::m_isInit)
		{
			UI::InitImGUI();
		}
		m_guiActive = !m_guiActive;
	}
	if (Input::GetKeyUp(Key::F4)) {
		printf("F4 Key Released\n");
	}
	if (Input::GetKeyUp(Key::Space)&& IsFlying == true) {
		IsFlying = false;
		body->SetGravityScale(1);
	}
	if (Input::GetKeyUp(Key::P)) {
		PhysicsBody::SetDraw(!PhysicsBody::GetDraw());
	}



}

void Game::MouseMotion(SDL_MouseMotionEvent evnt)
{

	handangle = PlayerActionController::HandRotation(m_activeScene, evnt);

	ECS::GetComponent<Transform>(EntityIdentifier::WeaponHand()).SetRotationAngleZ(handangle + Transform::ToRadians(180.f));


	auto& PlayerAnim = ECS::GetComponent<AnimationController>(EntityIdentifier::MainPlayer());
	auto& HandAnum = ECS::GetComponent<AnimationController>(EntityIdentifier::WeaponHand());
	if (handangle + Transform::ToRadians(180.f)>= PI/2&& handangle + Transform::ToRadians(180.f)<= (3*PI)/2) {
		HandAnum.SetActiveAnim(1);
		LOR = -1;
		if (IsFlying == true) {
			AnimNum = 5;
		}
		else if (IsFlying == false && ECS::GetComponent<PhysicsBody>(EntityIdentifier::MainPlayer()).GetBody()->GetLinearVelocity().x == 0)
			AnimNum = 1;
		else {
			AnimNum = 3;
		}
	}
	else {
		HandAnum.SetActiveAnim(0);
		LOR = 1;
		if (IsFlying == true) {
			AnimNum = 4;
		}
		else if (IsFlying == false && ECS::GetComponent<PhysicsBody>(EntityIdentifier::MainPlayer()).GetBody()->GetLinearVelocity().x == 0) {
			AnimNum = 0;
		}
		else {
			AnimNum = 2;
		}		
	}
	PlayerAnim.SetActiveAnim(AnimNum);
	//Resets the enabled flag
	m_motion = false;


	//Need to convert clicked point to screen space first!
/*vec2 clickedPoint = vec2(float(evnt.x), float(evnt.y));

float glX = (tempCam.GetAspect() * (tempCam.GetOrthoSize().y) - tempCam.GetAspect() * (tempCam.GetOrthoSize().x));
float glY = (tempCam.GetOrthoSize().w - tempCam.GetOrthoSize().z);

//Spaces
vec2 glSpace = vec2(glX, glY);

vec2 percentPoint = vec2(clickedPoint.x / windowSpace.x, clickedPoint.y / windowSpace.y);

//in glspace
clickedPoint = vec2(glSpace.x * percentPoint.x, glSpace.y * percentPoint.y);
clickedPoint = clickedPoint + vec2(tempCam.GetAspect() * tempCam.GetOrthoSize().x, tempCam.GetOrthoSize().z);
clickedPoint = clickedPoint + vec2(tempCam.GetPositionX(), tempCam.GetPositionY());*/

}

void Game::MouseClick(SDL_MouseButtonEvent evnt)
{
	if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT)) {
		PlayerActionController::Shoot(m_activeScene, handangle);

		Camera tempCam = ECS::GetComponent<Camera>(EntityIdentifier::MainCamera());
		vec2 windowSpace = vec2(float(BackEnd::GetWindowWidth()), float(BackEnd::GetWindowHeight()));
		vec2 position = vec2(tempCam.GetPositionX(), tempCam.GetPositionY());
		vec2 clickedPoint = vec2(
			(evnt.x / windowSpace.x - 0.5f) * tempCam.GetAspect() * tempCam.GetOrthoSize().w * 2,
			-(evnt.y / windowSpace.y - 0.5f) * tempCam.GetOrthoSize().w * 2
		);
		clickedPoint = clickedPoint + position;
		cout << "clickpos:" << clickedPoint.x << ", " << clickedPoint.y << endl;

		point.push_back(clickedPoint);
		
		//ClickCounter is the size of the array
		ClickCounter = ClickCounter + 1;

	}

	if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_RIGHT)) {
		printf("b2Vec2 WallPos[] = {");
		for (int x = 0; x < ClickCounter; x++) {
			if (x != ClickCounter - 1) {
				cout <<"b2Vec2("<< point[x].x << " , " << point[x].y << ")," << endl;
			}else{
				cout << "b2Vec2("<< point[x].x << " , " << point[x].y <<") };"<< endl;
			}
		}

	}

	if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_MIDDLE)) {
		printf("Middle Mouse Button Clicked at (%f, %f)\n", float(evnt.x), float(evnt.y));

	}


	m_activeScene->MouseClick(evnt);

	if (m_guiActive)
	{
		ImGui::GetIO().MousePos = ImVec2(float(evnt.x), float(evnt.y));
		ImGui::GetIO().MouseDown[0] = (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT));
		ImGui::GetIO().MouseDown[1] = (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_RIGHT));
		ImGui::GetIO().MouseDown[2] = (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_MIDDLE));
	}

	//Resets the enabled flag
	m_click = false;
}

void Game::MouseWheel(SDL_MouseWheelEvent evnt)
{
	printf("Mouse Scroll %f\n", float(evnt.y));
	m_activeScene->MouseWheel(evnt);

	if (m_guiActive)
	{
		ImGui::GetIO().MouseWheel = float(evnt.y);
	}

	//Resets the enabled flag
	m_wheel = false;
}

