#pragma once
#include "AsteroidsManager.h"
#include "../sdlutils/SDLUtils.h"

void AsteroidsManager::createAsteroid(int n)
{
	for (int i = 0; i < n; i++)
	{
		Vector2D nPos = Vector2D(sdlutils().rand().nextInt(0, WIN_WIDTH), sdlutils().rand().nextInt(0, WIN_HEIGHT));
		if (sdlutils().rand().nextInt(0, 10) > 3)
		{
			Entity* asteroidA = mngr->addEntity();
			asteroidA->addComponent<Transform>(nPos, Vector2D(sdlutils().rand().nextInt(-1, 1), sdlutils().rand().nextInt(-1, 1)) * 50, 50, 50, 0);
			asteroidA->addComponent<ShowAtOppositeSide>();
			asteroidA->addComponent<FramedImage>(Game::getTexture("Asteroid"), 50, 6, 5);
			asteroidA->addComponent<Generations>(1);
			asteroidA->setGroup(_grp_ASTEROIDS);
		}
		else
		{
			Entity* asteroidB = mngr->addEntity();
			asteroidB->addComponent<Transform>(nPos, Vector2D(sdlutils().rand().nextInt(-1, 1), sdlutils().rand().nextInt(-1, 1)) * 50, 50, 50, 0);
			asteroidB->addComponent<ShowAtOppositeSide>();
			asteroidB->addComponent<FramedImage>(Game::getTexture("AsteroidG"), 50, 6, 5);
			asteroidB->addComponent<Generations>(1);
			asteroidB->addComponent<Follow>(ship->getComponent<Transform>());
			asteroidB->setGroup(_grp_ASTEROIDS);
		}
		asteroidsAlive++;
	}
}


void AsteroidsManager::addAsteroidFrequently() {
	timer += Game::instance()->getDeltaTime();
	if (timer > 5000&&asteroidsAlive<=30) {
		createAsteroid(1);
		timer = 0;
	}
}

void AsteroidsManager::destroyAllAsteroids() {
	for (auto e : mngr->getEntities())
	{
		if (e->getGroup() == _grp_ASTEROIDS) {
			e->setAlive(false);
		}
	}
}

void AsteroidsManager::onCollision(Entity* asteroid) {
	asteroid->setAlive(false);
	int pGen = asteroid->getComponent<Generations>()->getGen();
	
	if (pGen < 3) {
		Transform* asteroidData = asteroid->getComponent<Transform>();
		for (int i = 0; i < 2 && asteroidsAlive <= 30; i++) {
			if (sdlutils().rand().nextInt(0, 10) > 3)
			{
				Entity* asteroidA = mngr->addEntity();
				asteroidA->addComponent<Transform>(asteroidData->getPos(), Vector2D(sdlutils().rand().nextInt(-1, 1), sdlutils().rand().nextInt(-1, 1)) * 50, asteroidData->getWidth()/2, asteroidData->getHeight()/2, 0);
				asteroidA->addComponent<ShowAtOppositeSide>();
				asteroidA->addComponent<FramedImage>(Game::getTexture("Asteroid"), 50, 6, 5);
				asteroidA->addComponent<Generations>(pGen+1);
				asteroidA->setGroup(_grp_ASTEROIDS);
			}
			else
			{
				Entity* asteroidB = mngr->addEntity();
				asteroidB->addComponent<Transform>(asteroidData->getPos(), Vector2D(sdlutils().rand().nextInt(-1, 1), sdlutils().rand().nextInt(-1, 1)) * 50, asteroidData->getWidth()/2, asteroidData->getHeight()/2, 0);
				asteroidB->addComponent<ShowAtOppositeSide>();
				asteroidB->addComponent<FramedImage>(Game::getTexture("AsteroidG"), 50, 6, 5);
				asteroidB->addComponent<Generations>(pGen+1);
				asteroidB->addComponent<Follow>(ship->getComponent<Transform>());
				asteroidB->setGroup(_grp_ASTEROIDS);
			}
			asteroidsAlive++;
		}
	}
		
		
}
