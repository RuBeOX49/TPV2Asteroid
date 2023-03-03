#include "CollisionsManager.h"
#include "../ecs/Entity.h"
#include "../utils/Collisions.h"
#include "../components/Transform.h"
#include "../components/Health.h"
#include "../game/GameStateMachine.h"
#include "../game/PauseState.h"
#include "../game/DamagedState.h"
#include "../game/DeathState.h"



void CollisonsManager::handlePhysics()
{
	for ( auto e : mngr->getEntities())
	{
		if (e->getGroup() == _grp_ASTEROIDS) {
			for (auto c : mngr->getEntities())
			{

				if(c->getGroup() == _grp_BULLETS)
				{
					Transform* eTr = e->getComponent<Transform>();
					Transform* cTr = c->getComponent<Transform>();

					if(Collisions::collidesWithRotation(eTr->getPos(), eTr->getWidth(), eTr->getHeight(), eTr->getRotation(),
						cTr->getPos(), cTr->getWidth(), cTr->getHeight(), cTr->getRotation() )) {
						//hay colisión, e desaparece

						astMngr->onCollision(e);
					}
					
				}

				if (c->getGroup() == _grp_FIGHTER)
				{
					Transform* eTr = e->getComponent<Transform>();
					Transform* cTr = c->getComponent<Transform>();

					if (Collisions::collidesWithRotation(eTr->getPos(), eTr->getWidth(), eTr->getHeight(), eTr->getRotation(),
						cTr->getPos(), cTr->getWidth(), cTr->getHeight(), cTr->getRotation())) {
						//hay colisión, e y c desaparecen ()
						std::cout << "funca\n";

						e->setAlive(false);


						auto hComponent = c->getComponent<HealthComponent>();
						
						hComponent->damage(1);

						if (hComponent->getLives() == 0) {
							astMngr->destroyAllAsteroids();
							GameStateMachine::instance()->pushState(new DeathState());
						}
						else {
						GameStateMachine::instance()->pushState(new DamagedState());
						}
						
					}

				}



			}
		}
	}
}
