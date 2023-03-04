#pragma once
#include "AsteroidsManager.h"
#include "../sdlutils/SDLUtils.h"

//Genera él número de asteroides n en una posición aleatoria del borde
void AsteroidsManager::createAsteroid(int n)
{
	for (int i = 0; i < n; i++)
	{
		//Se escoge un borde de la pantalla
		int n = sdlutils().rand().nextInt(1, 5);
		Vector2D nPos;
		switch (n) {
		case 1:
			nPos = Vector2D(0,sdlutils().rand().nextInt(0,WIN_HEIGHT));
			break;
		case 2:
			nPos = Vector2D(sdlutils().rand().nextInt(0, WIN_WIDTH),0);
			break;
		case 3:
			nPos = Vector2D(WIN_HEIGHT, sdlutils().rand().nextInt(0, WIN_HEIGHT));
			break;
		case 4:
			nPos = Vector2D(sdlutils().rand().nextInt(0, WIN_WIDTH), WIN_WIDTH);
			break;
		}
		Vector2D c = Vector2D(WIN_WIDTH / 2, WIN_HEIGHT) + Vector2D(sdlutils().rand().nextInt(-100, 100), sdlutils().rand().nextInt(-100, 100));
		float speed = sdlutils().rand().nextInt(10, astSpeed);
		Vector2D v = (c - nPos).normalize() * speed;

		//Se genera un asteroide tipo gris con un 70% y uno dorado con un 30%
		if (sdlutils().rand().nextInt(0, 10) > 3)
		{
			Entity* asteroidA = mngr->addEntity();
			asteroidA->addComponent<Transform>(nPos, v, 50, 50, 0);
			asteroidA->addComponent<ShowAtOppositeSide>();
			asteroidA->addComponent<FramedImage>(Game::getTexture("Asteroid"), 50, 6, 5);
			asteroidA->addComponent<Generations>(1);
			asteroidA->setGroup(_grp_ASTEROIDS);
		}
		else
		{
			Entity* asteroidB = mngr->addEntity();
			asteroidB->addComponent<Transform>(nPos, v , 50, 50, 0);
			asteroidB->addComponent<ShowAtOppositeSide>();
			asteroidB->addComponent<FramedImage>(Game::getTexture("AsteroidG"), 50, 6, 5);
			asteroidB->addComponent<Generations>(1);
			asteroidB->addComponent<Follow>(ship->getComponent<Transform>());
			asteroidB->setGroup(_grp_ASTEROIDS);
		}
		asteroidsAlive++;
	}
}


//Cada 5 segundos se crea un nuevo asteroide
void AsteroidsManager::addAsteroidFrequently() {
	timer += Game::instance()->getDeltaTime();
	if (timer > 5000&&asteroidsAlive<=30) {
		createAsteroid(1);
		timer = 0;
	}
}

//Destruye todos los asteroides
void AsteroidsManager::destroyAllAsteroids() {
	//Recorre todos los objetos y encuentra aquellos con el tag específico de asteroides
	for (auto e : mngr->getEntities())
	{
		if (e->getGroup() == _grp_ASTEROIDS) {
			e->setAlive(false);
		}
	}
}


//Al colisionar 
void AsteroidsManager::onCollision(Entity* asteroid) {
	asteroid->setAlive(false);
	int pGen = asteroid->getComponent<Generations>()->getGen();
	//Si la generación es menor que 3 se genera un nuevo asteroide
	if (pGen < 3) {
		//Se genera en la posción específica
		Transform* asteroidData = asteroid->getComponent<Transform>();
		for (int i = 0; i < 2 && asteroidsAlive <= 30; i++) {

			Vector2D c = Vector2D(WIN_WIDTH / 2, WIN_HEIGHT) + Vector2D(sdlutils().rand().nextInt(-100, 100), sdlutils().rand().nextInt(-100, 100));
			float speed = sdlutils().rand().nextInt(10, astSpeed);
			Vector2D v = (c - asteroidData->getPos()).normalize() * speed;

			//Se genera un asteroide tipo gris con un 70% y uno dorado con un 30%
			if (sdlutils().rand().nextInt(0, 10) > 3)
			{
				Entity* asteroidA = mngr->addEntity();
				asteroidA->addComponent<Transform>(asteroidData->getPos(), v, asteroidData->getWidth()/2, asteroidData->getHeight()/2, 0);
				asteroidA->addComponent<ShowAtOppositeSide>();
				asteroidA->addComponent<FramedImage>(Game::getTexture("Asteroid"), 50, 6, 5);
				asteroidA->addComponent<Generations>(pGen+1);
				asteroidA->setGroup(_grp_ASTEROIDS);
			}
			else
			{
				Entity* asteroidB = mngr->addEntity();
				asteroidB->addComponent<Transform>(asteroidData->getPos(), v, asteroidData->getWidth()/2, asteroidData->getHeight()/2, 0);
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
