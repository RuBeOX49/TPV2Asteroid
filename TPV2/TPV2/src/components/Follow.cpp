#pragma once
#include "Follow.h"
#include "../ecs/Entity.h"


void Follow::initComponent()
{
	asteroidTransform = ent->getComponent<Transform>();
}

void Follow::update()
{
	asteroidTransform->lookAt(playerTransform->getPos());
}
