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
			mngr->addComponent<Transform>(asteroidA, nPos, v, 50, 50, 0);
			//mngr->addComponent<ShowAtOppositeSide>(asteroidA);
			mngr->addComponent<FramedImage>(asteroidA, Game::getTexture("Asteroid"), 50.0, 6, 5, true);
			mngr->addComponent<Generations>(asteroidA, 1);
			asteroidA->setGroup(_grp_ASTEROIDS);
		}
		else
		{
			Entity* asteroidB = mngr->addEntity();
			mngr->addComponent<Transform>(asteroidB, nPos, v , 50, 50, 0);
			//mngr->addComponent<ShowAtOppositeSide>(asteroidB);
			mngr->addComponent<FramedImage>(asteroidB, Game::getTexture("AsteroidG"), 50.0, 6, 5, true);
			mngr->addComponent<Generations>(asteroidB, 1);
			mngr->addComponent<Follow>(asteroidB, mngr->getComponent<Transform>(ship));
			asteroidB->setGroup(_grp_ASTEROIDS);
		}
		asteroidsAlive++;
	}
}


//Cada 5 segundos se crea un nuevo asteroide
void AsteroidsManager::addAsteroidFrequently() {
	timer += Game::instance()->getDeltaTime();
	if (timer > 5000 && asteroidsAlive<=30) {
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
	brokenAsteroid->play();
	asteroid->setAlive(false);
	int pGen = mngr->getComponent<Generations>(asteroid)->getGen();
	//Si la generación es menor que 3 se genera un nuevo asteroide
	if (pGen < 3) {
		//Se genera en la posción específica
		Transform* asteroidData = mngr->getComponent<Transform>(asteroid);
		for (int i = 0; i < 2 && asteroidsAlive <= 30; i++) {

			Vector2D c = Vector2D(WIN_WIDTH / 2, WIN_HEIGHT) + Vector2D(sdlutils().rand().nextInt(-100, 100), sdlutils().rand().nextInt(-100, 100));
			float speed = sdlutils().rand().nextInt(10, astSpeed);
			Vector2D v = (c - asteroidData->getPos()).normalize() * speed;

			//Se genera un asteroide tipo gris con un 70% y uno dorado con un 30%
			if (sdlutils().rand().nextInt(0, 10) > 3)
			{
				Entity* asteroidA = mngr->addEntity();
				mngr->addComponent<Transform>(asteroidA, asteroidData->getPos(), v, asteroidData->getWidth()/2, asteroidData->getHeight()/2, 0);
				//mngr->addComponent<ShowAtOppositeSide>(asteroidA);
				mngr->addComponent<FramedImage>(asteroidA, Game::getTexture("Asteroid"), 50.0, 6, 5, true);
				mngr->addComponent<Generations>(asteroidA, pGen+1);
				asteroidA->setGroup(_grp_ASTEROIDS);
			}
			else
			{
				Entity* asteroidB = mngr->addEntity();
				mngr->addComponent<Transform>(asteroidB, asteroidData->getPos(), v, asteroidData->getWidth()/2, asteroidData->getHeight()/2, 0);
				//mngr->addComponent<ShowAtOppositeSide>(asteroidB);
				mngr->addComponent<FramedImage>(asteroidB, Game::getTexture("AsteroidG"), 50.0, 6, 5, true);
				mngr->addComponent<Generations>(asteroidB, pGen+1);
				mngr->addComponent<Follow>(asteroidB, mngr->getComponent<Transform>(ship));
				asteroidB->setGroup(_grp_ASTEROIDS);
			}
			asteroidsAlive++;
		}
	}
		
		
}
