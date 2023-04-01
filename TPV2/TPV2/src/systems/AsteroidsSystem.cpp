#pragma once
#include "../ecs/System.h"
#include "AsteroidsSystem.h"
#include "../components/Transform.h"
#include "../components/Follow.h"
#include "../components/Generations.h"
#include "../components/FramedImage.h"
#include "../game/Game.h"

//Maneja los casos de cada mensaje
void AsteroidsSystem::receive(const Message& m)
{
	switch (m.id)
	{
	case _m_BATTLE_STATE_SETUP:
		onRoundStart();
		break;
	case _m_CHANGE_STATE:
		if (m.new_state_ID.state != state_BATTLE)
			active_ = false;
		else active_ = true;
		break;
	case _m_COLLISION_AST_BULLET:
		onCollision_AsteroidBullet(m.destroy_asteroid_data.e);
		break;
	case _m_COLLISION_AST_SHIP:
		mngr_->setAlive(m.destroy_asteroid_data.e, false);
		break;
	default:
		
		break;
	}
}

//Cogemos la referencia del sonido de destruccion del asteroide
void AsteroidsSystem::initSystem()
{
	brokenAsteroid = &sdlutils().soundEffects().at("Explosion");
	brokenAsteroid->setVolume(10);
}

//Mueve los asteroides, dirige el comportamiento especial del follow
//y llama al metodo de generacio
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
		
			Vector2D pos = transform->getPos();

			if (pos.getX() < 0 - transform->getWidth()) {

				transform->setX(WIN_WIDTH);
			}
			else if (pos.getX() > WIN_WIDTH) {
				transform->setX(0 - transform->getWidth());
			}

			if (pos.getY() < 0 - transform->getHeight()) {
				transform->setY(WIN_HEIGHT);
			}
			else if (pos.getY() > WIN_HEIGHT) {
				transform->setY(0 - transform->getHeight());
			}
		}
	
		
	}

	addAsteroidFrequently();
	
}

//Gestiona la reaccion del asteroide al colisionar con un disparo, se destruye
//y si no hay más de 30 se genera uno nuevo
void AsteroidsSystem::onCollision_AsteroidBullet(Entity* asteroid)
{
	brokenAsteroid->play();
	mngr_->setAlive(asteroid, false);
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
				mngr_->addComponent<FramedImage>(asteroidA, Game::getTexture("Asteroid"), 50.0, 6, 5, true);
				mngr_->addComponent<Generations>(asteroidA, pGen + 1);
				asteroidA->setGroup(_grp_ASTEROIDS);
			}
			else
			{
				Entity* asteroidB = mngr_->addEntity();
				mngr_->addComponent<Transform>(asteroidB, asteroidData->position_, v, asteroidData->width_ / 2, asteroidData->height_ / 2, 0);
				mngr_->addComponent<FramedImage>(asteroidB, Game::getTexture("AsteroidG"), 50.0, 6, 5, true);
				mngr_->addComponent<Generations>(asteroidB, pGen + 1);
				mngr_->addComponent<Follow>(asteroidB, mngr_->getComponent<Transform>(fighter));
				asteroidB->setGroup(_grp_ASTEROIDS);
			}
			numOfAsteroids_++;
		}
	}


}

//Se desactiva el sistema y se destruyen todos los asteroides restantes
void AsteroidsSystem::onRoundOver()
{
	active_ = false;
	destroyAllAsteroids();
}

//Al empezar una partida se activa el sistema, se reinicia el numero
//de asteroides, se asigna el fighter y se crean 10 asteroides
void AsteroidsSystem::onRoundStart()
{
	numOfAsteroids_ = 0;
	active_ = true;
	for (auto var : mngr_->getEntities()) {
		if (var->getGroup() == _grp_FIGHTER)
			fighter = var;
	}
	createAsteroid(10);
}

//Genera un número específico de asteroides
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
			mngr_->addComponent<FramedImage>(asteroidA, Game::getTexture("Asteroid"), 50.0, 6, 5, true);
			mngr_->addComponent<Generations>(asteroidA, 1);
			asteroidA->setGroup(_grp_ASTEROIDS);
		}
		else
		{
			Entity* asteroidB = mngr_->addEntity();
			mngr_->addComponent<Transform>(asteroidB, nPos, v, 50, 50, 0);
			mngr_->addComponent<FramedImage>(asteroidB, Game::getTexture("AsteroidG"), 50.0, 6, 5, true);
			mngr_->addComponent<Generations>(asteroidB, 1);
			mngr_->addComponent<Follow>(asteroidB, mngr_->getComponent<Transform>(fighter));
			asteroidB->setGroup(_grp_ASTEROIDS);
		}
		numOfAsteroids_++;
	}
}

//Cada 5 segundos se añade un nuevo asteroide
//si no se ha alcanzado el límitede 30
void AsteroidsSystem::addAsteroidFrequently()
{
	timer += Game::instance()->getDeltaTime();
	if (timer > 5000 && numOfAsteroids_ <= 30) {
		createAsteroid(1);
		timer = 0;
	}
}

//Destruyo todos los asteroides de la escena
void AsteroidsSystem::destroyAllAsteroids()
{
	for (auto e : mngr_->getEntities())
	{
		if (e->getGroup() == _grp_ASTEROIDS) {
			e->setAlive(false);
		}
	}
}
