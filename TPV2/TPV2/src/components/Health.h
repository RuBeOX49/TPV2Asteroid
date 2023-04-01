#pragma once
#include "../ecs/Component.h"
#include "../game/constants.h"
#include "../sdlutils/Texture.h"
#include "../game/Game.h"
class HealthComponent : public Component
{
private:
	int currLives=STARTING_HEALTH;
	Texture* healthTexture;

public:

	static const int id = _HEALTH;
	HealthComponent() {
		healthTexture = Game::getTexture("Heart");
	}

	virtual ~HealthComponent() {};

	//Devuelve las vidas restantes
	inline int getLives() { return currLives; }
	//Reinicia las vidas al valor por defecto
	inline void resetLives() { currLives = STARTING_HEALTH; }
	//Reduce "damage" vidas del total
	inline void damage(int damage) { currLives -= damage; }

};



