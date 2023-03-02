#include "CollisionsManager.h"
#include "../ecs/Entity.h"
#include "../utils/Collisions.h"
#include "../components/Transform.h"

void CollisonsManager::handlePhysics()
{
	for ( auto e : mngrRef->getEntities())
	{
		if (e->getGroup() == _grp_ASTEROIDS) {
			for (auto c : mngrRef->getEntities())
			{

				if(c->getGroup() == _grp_BULLETS)
				{
					Transform* eTr = e->getComponent<Transform>();
					Transform* cTr = c->getComponent<Transform>();

					if(Collisions::collidesWithRotation(eTr->getPos(), eTr->getWidth(), eTr->getHeight(), eTr->getRotation(),
						cTr->getPos(), cTr->getWidth(), cTr->getHeight(), cTr->getRotation() )) {
						//hay colisión, e desaparece
					}
					
				}

				if (c->getGroup() == _grp_FIGHTER)
				{
					Transform* eTr = e->getComponent<Transform>();
					Transform* cTr = c->getComponent<Transform>();

					if (Collisions::collidesWithRotation(eTr->getPos(), eTr->getWidth(), eTr->getHeight(), eTr->getRotation(),
						cTr->getPos(), cTr->getWidth(), cTr->getHeight(), cTr->getRotation())) {
						//hay colisión, c desaparece
						std::cout << "funca";
					}

				}



			}
		}
	}
}
