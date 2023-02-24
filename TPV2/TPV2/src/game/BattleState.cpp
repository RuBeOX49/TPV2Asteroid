#pragma once
#include "BattleState.h"
#include "../ecs/Entity.h"
#include "../components/allComponents.h"
BattleState::BattleState()
{
	mngr = new Manager();

	//LA NAVE

	Entity* ship = mngr->addEntity();
	ship->addComponent<Transform>();
	ship->addComponent<HealthComponent>();
	/*
	ship->addComponent<DeAcceleration>();
	ship->addComponent<Image>();
	ship->addComponent<FighterCtrl>();
	ship->addComponent<Gun>();
	ship->addComponent<ShowAtOppositeSide>();
	*/
}

BattleState::~BattleState()
{
}
