#pragma once
#include "../ecs/Component.h"
#include "../game/constants.h"
#include "../sdlutils/Texture.h"
class HealthComponent : public Component
{
private:
	int currLives;
	Texture* healthTexture;

public:

	static const int id = _HEALTH;
	HealthComponent();

	virtual ~HealthComponent();

	virtual void render() const;

	inline int getLives() { return currLives; }
	inline void resetLives() { currLives = STARTING_HEALTH; }
	inline void damage(int damage);
};



