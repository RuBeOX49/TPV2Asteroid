#include "CollisionsManager.h"
#include "../ecs/Entity.h"
#include "../utils/Collisions.h"
#include "../components/Transform.h"
#include "../components/Health.h"
#include "../game/GameStateMachine.h"
#include "../game/PauseState.h"
#include "../game/DamagedState.h"
#include "../game/DeathState.h"
#include "AsteroidsManager.h"
#include "../ecs/Manager.h"



void CollisonsManager::handlePhysics()
{
	for ( auto e : mngr->getEntities())
	{
		if (e->getGroup() == _grp_ASTEROIDS) {
			for (auto c : mngr->getEntities())
			{
				if(c->getGroup() == _grp_BULLETS)
				{
					handleBulletCollision(e, c);
				}

				if (c->getGroup() == _grp_FIGHTER)
				{
					
					handleFighterCollision(e, c);
				}
			}
		}
	}
}

void CollisonsManager::handleBulletCollision( Entity* e,  Entity* c)
{
	Transform* eTr = e->getComponent<Transform>();
	Transform* cTr = c->getComponent<Transform>();

	if (Collisions::collidesWithRotation(eTr->getPos(), eTr->getWidth(), eTr->getHeight(), eTr->getRotation(),
		cTr->getPos(), cTr->getWidth(), cTr->getHeight(), cTr->getRotation())) {
		//hay colisi�n, e desaparece

		astMngr->onCollision(e);
	}
}

void CollisonsManager::handleFighterCollision( Entity* e,  Entity* c)
{
	Transform* eTr = e->getComponent<Transform>();
	Transform* cTr = c->getComponent<Transform>();

	if (Collisions::collidesWithRotation(eTr->getPos(), eTr->getWidth(), eTr->getHeight(), eTr->getRotation(),
		cTr->getPos(), cTr->getWidth(), cTr->getHeight(), cTr->getRotation())) {
		explosion->play();
		//hay colisi�n, e y c desaparecen ()

		e->setAlive(false);

		auto hComponent = c->getComponent<HealthComponent>();

		hComponent->damage(1);

		if (hComponent->getLives() == 0) {
			astMngr->destroyAllAsteroids();
			GameStateMachine::instance()->changeState(new DeathState());
		}
		else {
			GameStateMachine::instance()->pushState(new DamagedState());
		}
	}
}
