#pragma once
#include "../ecs/System.h"
#include "AsteroidsSystem.h"
#include "../components/Transform.h"
#include "../components/Follow.h"
#include "../components/ShowAtOppositeSide.h"
#include "../components/Generations.h"
#include "../components/FramedImage.h"
#include "../game/Game.h"


void AsteroidsSystem::receive(const Message& m)
{
	switch (m.id)
	{
	case _m_BATTLE_STATE_SETUP:
		onRoundStart();
		active_ = true;

	default:
		break;
	}
}

void AsteroidsSystem::initSystem()
{
}

void AsteroidsSystem::update()
{
	if (!active_)
		return;

	//Movimiento de asteroides

	for (auto var : mngr_->getEntities())
	{
		if (var->getGroup() == _grp_ASTEROIDS)
		{
			auto transform = mngr_->getComponent<Transform>(var);
			
			if (mngr_->hasComponent<Follow>(var))
			{
				//void Transform::lookAt(Vector2D point)

				auto point = mngr_->getComponent<Transform>(fighter)->position_;

				Vector2D aux = point - transform->position_; // Saca el vector desde el punto a la posición
				float rotation = transform->velocity_.angle(aux); // Saca los angulos entre el vector velocidad y el necesario
				transform->velocity_ = transform->velocity_.rotate(rotation); // Rota el vector velocidad
			}

			transform->position_ = transform->position_ + (transform->velocity_ * Game::instance()->getDeltaTimeSeconds());
		
			Vector2D pos = transform->position_;

			if (pos.getX() < 0 - transform->width_) {

				pos.setX(WIN_WIDTH);
			}
			else if (pos.getX() > WIN_WIDTH) {
				pos.setX(0 - transform->width_);
			}

			if (pos.getY() < 0 - transform->height_) {
				pos.setY(WIN_HEIGHT);
			}
			else if (pos.getY() > WIN_HEIGHT) {
				pos.setY(0 - transform->height_);
			}
		}
	
		
	}

	addAsteroidFrequently();
	
}

void AsteroidsSystem::onCollision_AsteroidBullet(Entity* asteroid)
{
	brokenAsteroid->play();
	asteroid->setAlive(false);
	int pGen = mngr_->getComponent<Generations>(asteroid)->getGen();
	//Si la generación es menor que 3 se genera un nuevo asteroide
	if (pGen < 3) {
		//Se genera en la posción específica
		Transform* asteroidData = mngr_->getComponent<Transform>(asteroid);
		for (int i = 0; i < 2 && numOfAsteroids_ <= 30; i++) {

			Vector2D c = Vector2D(WIN_WIDTH / 2, WIN_HEIGHT) + Vector2D(sdlutils().rand().nextInt(-100, 100), sdlutils().rand().nextInt(-100, 100));
			float speed = sdlutils().rand().nextInt(10, astSpeed);
			Vector2D v = (c - asteroidData->position_).normalize() * speed;

			//Se genera un asteroide tipo gris con un 70% y uno dorado con un 30%
			if (sdlutils().rand().nextInt(0, 10) > 3)
			{
				Entity* asteroidA = mngr_->addEntity();
				mngr_->addComponent<Transform>(asteroidA, asteroidData->position_, v, asteroidData->width_ / 2, asteroidData->height_ / 2, 0);
				mngr_->addComponent<ShowAtOppositeSide>(asteroidA);
				mngr_->addComponent<FramedImage>(asteroidA, Game::getTexture("Asteroid"), 50.0, 6, 5, true);
				mngr_->addComponent<Generations>(asteroidA, pGen + 1);
				asteroidA->setGroup(_grp_ASTEROIDS);
			}
			else
			{
				Entity* asteroidB = mngr_->addEntity();
				mngr_->addComponent<Transform>(asteroidB, asteroidData->position_, v, asteroidData->width_ / 2, asteroidData->height_ / 2, 0);
				mngr_->addComponent<ShowAtOppositeSide>(asteroidB);
				mngr_->addComponent<FramedImage>(asteroidB, Game::getTexture("AsteroidG"), 50.0, 6, 5, true);
				mngr_->addComponent<Generations>(asteroidB, pGen + 1);
				mngr_->addComponent<Follow>(asteroidB, mngr_->getComponent<Transform>(fighter));
				asteroidB->setGroup(_grp_ASTEROIDS);
			}
			numOfAsteroids_++;
		}
	}


}

void AsteroidsSystem::onRoundOver()
{
	destroyAllAsteroids();
}

void AsteroidsSystem::onRoundStart()
{
	for (auto var : mngr_->getEntities()) {
		if (var->getGroup() == _grp_FIGHTER)
			fighter = var;
	}
	createAsteroid(10);
}

void AsteroidsSystem::createAsteroid(int n)
{
	for (int i = 0; i < n; i++)
	{
		//Se escoge un borde de la pantalla
		int n = sdlutils().rand().nextInt(1, 5);
		Vector2D nPos;
		switch (n) {
		case 1:
			nPos = Vector2D(0, sdlutils().rand().nextInt(0, WIN_HEIGHT));
			break;
		case 2:
			nPos = Vector2D(sdlutils().rand().nextInt(0, WIN_WIDTH), 0);
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
			Entity* asteroidA = mngr_->addEntity();
			mngr_->addComponent<Transform>(asteroidA, nPos, v, 50, 50, 0);
			mngr_->addComponent<ShowAtOppositeSide>(asteroidA);
			mngr_->addComponent<FramedImage>(asteroidA, Game::getTexture("Asteroid"), 50.0, 6, 5, true);
			mngr_->addComponent<Generations>(asteroidA, 1);
			asteroidA->setGroup(_grp_ASTEROIDS);
		}
		else
		{
			Entity* asteroidB = mngr_->addEntity();
			mngr_->addComponent<Transform>(asteroidB, nPos, v, 50, 50, 0);
			mngr_->addComponent<ShowAtOppositeSide>(asteroidB);
			mngr_->addComponent<FramedImage>(asteroidB, Game::getTexture("AsteroidG"), 50.0, 6, 5, true);
			mngr_->addComponent<Generations>(asteroidB, 1);
			mngr_->addComponent<Follow>(asteroidB, mngr_->getComponent<Transform>(fighter));
			asteroidB->setGroup(_grp_ASTEROIDS);
		}
		numOfAsteroids_++;
	}
}

void AsteroidsSystem::addAsteroidFrequently()
{
	timer += Game::instance()->getDeltaTime();
	if (timer > 5000 && numOfAsteroids_ <= 30) {
		createAsteroid(1);
		timer = 0;
	}
}

void AsteroidsSystem::destroyAllAsteroids()
{
	for (auto e : mngr_->getEntities())
	{
		if (e->getGroup() == _grp_ASTEROIDS) {
			e->setAlive(false);
		}
	}
}
