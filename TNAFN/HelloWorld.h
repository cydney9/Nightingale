#pragma once

#include "Scene.h"
#include "ContactListener.h"

class HelloWorld : public Scene
{
public:
	HelloWorld(std::string name);

	virtual void InitScene(float windowWidth, float windowHeight) override;
protected:
	ContactListener listener;
};

