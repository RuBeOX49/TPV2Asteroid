#pragma once
#include "../ecs/System.h"
#include "AsteroidsSystem.h"
#include "../components/Transform.h"
#include "../components/Follow.h"
#include "../game/Game.h"


void AsteroidsSystem::receive(const Message& m)
{
	if(m.id == _m_SPAWN_ASTEROIDS)
	{
		// spawnInitialAsteroids();
	}
}

void AsteroidsSystem::initSystem()
{
}

void AsteroidsSystem::update()
{
	if (!active_)
		return;
	for (auto var : mngr_->getEntities())
	{
		if (var->getGroup() == _grp_ASTEROIDS)
		{
			auto transform = mngr_->getComponent<Transform>(var);
			
			if (mngr_->hasComponent<Follow>(var))
			{
				//void Transform::lookAt(Vector2D point)

				auto point = mngr_->getComponent<Transform>(fighter)->getPos();

				Vector2D aux = point - transform->position_; // Saca el vector desde el punto a la posición
				float rotation = transform->velocity_.angle(aux); // Saca los angulos entre el vector velocidad y el necesario
				transform->velocity_ = transform->velocity_.rotate(rotation); // Rota el vector velocidad
			}

			transform->position_ = transform->position_ + (transform->velocity_ * Game::instance()->getDeltaTimeSeconds());
		}
	}

	
}

void AsteroidsSystem::onCollision_AsteroidBullet(Entity* a)
{

}

void AsteroidsSystem::onRoundOver()
{

}

void AsteroidsSystem::onRoundStart()
{
	for (auto var : mngr_->getEntities()) {
		if (var->getGroup() == _grp_FIGHTER)
			fighter = var;
	}
}
