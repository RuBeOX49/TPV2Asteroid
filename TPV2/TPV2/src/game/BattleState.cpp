#pragma once
#include "BattleState.h"
#include "../ecs/Entity.h"
#pragma region allComponents
#include "../components/DeAcceleration.h"
#include "../components/DisableOnExit.h"
#include "../components/FighterCtrl.h"
#include "../components/Follow.h"
#include "../components/FramedImage.h"
#include "../components/Generations.h"
#include "../components/Gun.h"
#include "../components/Health.h"
#include "../components/Image.h"
#include "../components/ShowAtOppositeSide.h"
#include "../components/Transform.h"
#pragma endregion



BattleState::BattleState()
{
	mngr = new Manager();

	//LA NAVE

	Entity* ship = mngr->addEntity();
	ship->addComponent<Transform>();
	ship->addComponent<Image>();
	ship->addComponent<HealthComponent>();
	ship->addComponent<DeAcceleration>();
	//ship->addComponent<Image>();
	/*
	ship->addComponent<FighterCtrl>();
	ship->addComponent<Gun>();
	ship->addComponent<ShowAtOppositeSide>();
	*/
}

BattleState::~BattleState()
{
}
