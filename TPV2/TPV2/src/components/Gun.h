#pragma once
#include "../ecs/Component.h"
#include "Transform.h"

class Gun: public Component
{
private:

	//Music* shotSound;
	Uint32 lastTimeShot;
	Transform* shipData;

public:
	static const int id = _GUN;

	Gun();
	~Gun();

	virtual void handleEvents();
};

