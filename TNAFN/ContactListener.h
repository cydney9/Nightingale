#pragma once
#include <GL/glew.h>
#include <Box2D/Box2D.h>
#include "ECS.h"
#include <iostream>
#include "ContactList.h"

using namespace std;
class ContactListener : public b2ContactListener
{
public: 
	void BeginContact(b2Contact* contact);

	void EndContact(b2Contact* contact);

private:
};

inline void ContactListener::BeginContact(b2Contact* contact) {

	for (int x(0); x < ContactList::list.size(); x++) {
		void* fixtureUserData = contact->GetFixtureA()->GetUserData();
		int tempEntNum = ContactList::list[x];
		if ((int)fixtureUserData == tempEntNum) {
			ECS::GetComponent<PhysicsBody>(tempEntNum).SetIsGrounded(true);
		}
		fixtureUserData = contact->GetFixtureB()->GetUserData();
		if ((int)fixtureUserData == tempEntNum) {
			ECS::GetComponent<PhysicsBody>(tempEntNum).SetIsGrounded(true);
		}
	}

}
inline void ContactListener::EndContact(b2Contact* contact) {

	for (int x(0); x < ContactList::list.size(); x++) {
		void* fixtureUserData = contact->GetFixtureA()->GetUserData();
		int tempEntNum = ContactList::list[x];
		if ((int)fixtureUserData == tempEntNum) {
			ECS::GetComponent<PhysicsBody>(tempEntNum).SetIsGrounded(false);
		}

		fixtureUserData = contact->GetFixtureB()->GetUserData();

		if ((int)fixtureUserData == tempEntNum) {
			ECS::GetComponent<PhysicsBody>(tempEntNum).SetIsGrounded(false);
		}
	}
}
