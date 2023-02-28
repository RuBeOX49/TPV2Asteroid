#pragma once
#include "../ecs/Component.h"

class Gun: public Component
{
private:

	//Music* shotSound;
	Uint32 lastTimeShot;

public:
	Gun();
	~Gun();

	virtual void handleEvents();
};

