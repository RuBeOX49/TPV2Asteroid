#pragma once
#include "../ecs/Component.h"
class Transform;
class DeAcceleration : public Component
{
private:
	float deAccTimer=0;

public:

	static const int id = _DEACCELERATION;

	DeAcceleration(){}
	~DeAcceleration() {}
	inline float getDeAaccTimer() {
		return deAccTimer;
	}

	inline void setDeAccTimer(float newTime) {
		deAccTimer = newTime;
	}


};

