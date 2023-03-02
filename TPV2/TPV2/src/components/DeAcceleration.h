#pragma once
#include "../ecs/Component.h"
class Transform;
class DeAcceleration : public Component
{
private:

	Transform* transform;
	double deAccTimer=0;

public:

	static const int id = _DEACCELERATION;

	DeAcceleration() : transform(nullptr) {}
	~DeAcceleration() {}

	virtual void update();
	void initComponent();


};

