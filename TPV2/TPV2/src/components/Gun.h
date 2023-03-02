#pragma once
#include "../ecs/Component.h"
#include "Transform.h"

class Gun: public Component
{
private:

	//Music* shotSound;
	float lastTimeShot=250;
	Transform* shipData;

public:
	static const int id = _GUN;

	Gun();
	~Gun();

	virtual void initComponent();
	virtual void handleInput();
	virtual void update();
};

