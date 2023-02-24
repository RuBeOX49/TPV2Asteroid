#include "Health.h"

HealthComponent::HealthComponent() : currLives(STARTING_HEALTH)
{
}

HealthComponent::~HealthComponent()
{
}

void HealthComponent::render()
{
	for (int i = 0; i < currLives; i++)
	{
		//renderizar 1 corazon o algo en x = 20 + i * (textureSize + 10) , y = 20 
	}
}
