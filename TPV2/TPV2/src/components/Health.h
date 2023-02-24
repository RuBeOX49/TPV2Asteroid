#pragma once
#include "../ecs/Component.h"
#include "../game/constants.h"

class HealthComponent : public Component
{
private:
	int currLives;


public:

	static const int id = _HEALTH;
	HealthComponent();

	virtual ~HealthComponent();

	virtual void render();

	inline int getLives() { return currLives; }
	inline void resetLives() { currLives = STARTING_HEALTH; }
	
};



