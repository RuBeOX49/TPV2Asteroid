#pragma once
#include "AsteroidsManager.h"
#include "../sdlutils/SDLUtils.h"

void AsteroidsManager::createAsteroid(int n)
{
	for (int i = 0; i < n; i++)
	{
		if (sdlutils().rand().nextInt(0, 10) > 3)
		{
			//Tipo A
		}
		else
		{
			//Tipo B
		}
	}
}

