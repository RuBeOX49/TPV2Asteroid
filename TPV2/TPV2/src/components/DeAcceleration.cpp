#include "DeAcceleration.h"
#include "../ecs/Entity.h"
#include "Transform.h"
void DeAcceleration::update()
{
	if (this->ent->getComponent<Transform>()->getVel().magnitude() > 0.05) {
		this->ent->getComponent<Transform>()->setVel(
			this->ent->getComponent<Transform>()->getVel() * 0.995);
	}
	else
	{
		this->ent->getComponent<Transform>()->setVel(Vector2D(0, 0));
	}
}
