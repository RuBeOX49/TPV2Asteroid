#pragma once
#include "Follow.h"
#include "../ecs/Entity.h"


void Follow::initComponent()
{
	//asteroidTransform = ent->getComponent<Transform>();
}

//Cambia la velocidad hacia la posici�n del jugador
void Follow::update()
{
	asteroidTransform->lookAt(playerTransform->getPos());
}
