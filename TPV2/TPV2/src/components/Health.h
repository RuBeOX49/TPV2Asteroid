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
	//Devuelve las vidas restantes
	inline int getLives() { return currLives; }
	//Reinicia las vidas al valor por defecto
	inline void resetLives() { currLives = STARTING_HEALTH; }
	//Reduce "damage" vidas del total
	inline void damage(int damage) { currLives -= damage; }

};



