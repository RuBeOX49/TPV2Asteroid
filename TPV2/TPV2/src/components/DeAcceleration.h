#pragma once
#include "../ecs/Component.h"
class Transform;
class DeAcceleration : public Component
{
private:

	Transform* transform;
	float deAccTimer=0;

public:

	static const int id = _DEACCELERATION;

	DeAcceleration() : transform(nullptr) {}
	~DeAcceleration() {}

	virtual void update();
	void initComponent();


};

