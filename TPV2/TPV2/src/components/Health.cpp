#include "Health.h"
#include "../game/Game.h"


HealthComponent::HealthComponent() : currLives(STARTING_HEALTH)
{
	healthTexture = Game::getTexture("Heart");
}

HealthComponent::~HealthComponent()
{
}

void HealthComponent::render() const
{
	for (int i = 0; i < currLives; i++)
	{
		SDL_Rect rect = build_sdlrect(20 + i * (20 + 10), 20, 20, 20);
		healthTexture->render(rect);
		//renderizar 1 corazon o algo en x = 20 + i * (textureSize + 10) , y = 20 
	}
}


