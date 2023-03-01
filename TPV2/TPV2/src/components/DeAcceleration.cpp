#include "DeAcceleration.h"
#include "../ecs/Entity.h"
#include "Transform.h"


void DeAcceleration::initComponent() {
	transform = ent->getComponent<Transform>();
}


void DeAcceleration::update()
{
	if (transform->getVel().magnitude() > 0.05) {
		transform->setVel(transform->getVel() * 0.995);
	}
	else {
		transform->setVel(Vector2D(0, 0));
	}
}
