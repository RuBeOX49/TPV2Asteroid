#pragma once
#include "ecs.h"

class GameObject;
class Manager;
class Component
{
protected:
	GameObject* gameObject;
	Manager* manager;

public:
	Component() :gameObject(nullptr), manager(nullptr) {};
	virtual ~Component();

	inline void setContext(GameObject* gObject, Manager* mngr) {
		gameObject = gObject;
		manager = mngr;
	}

	virtual void render();
	virtual void update();
	virtual void handleEvents();
};

