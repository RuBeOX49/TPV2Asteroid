#pragma once
#include "../ecs/Component.h"
#include "Transform.h"
#include "../sdlutils/SDLUtils.h"

class Gun: public Component
{
private:

	int bSpeed=10;
	float lastTimeShot=250;
	
public:
	static const int id = _GUN;

	Gun() {};
	~Gun() {};

	virtual void initComponent() {  };
	virtual void handleInput() {};
	virtual void update() {};

	inline int getBulletSpeed() { return bSpeed; };
	inline float getLastTimeShot() { return lastTimeShot; };
	inline void setLastTimeShot(float newTime) { lastTimeShot = newTime; }
};

