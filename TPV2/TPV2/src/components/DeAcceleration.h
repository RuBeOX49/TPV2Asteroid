#pragma once
#include "../ecs/Component.h"
class DeAcceleration : public Component
{
private:


public:

	static const int id = _DEACCELERATION;

	DeAcceleration() {}
	~DeAcceleration() {}

	virtual void update();


};

