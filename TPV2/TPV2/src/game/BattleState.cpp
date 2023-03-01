#pragma once
#include "BattleState.h"
#include "../ecs/Entity.h"
#include "Game.h"
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
	//LA NAVE
	Entity* ship = mngr->addEntity();
	ship->setGroup(_grp_FIGHTER);
	ship->addComponent<Transform>(Vector2D(WIN_WIDTH / 2, WIN_HEIGHT / 2), Vector2D(), 100, 100, 0);
	ship->addComponent<HealthComponent>();
	ship->addComponent<DeAcceleration>();
	ship->addComponent<Image>(Game::getTexture("Ship"));
	ship->addComponent<FighterCtrl>();
	ship->addComponent<ShowAtOppositeSide>();
	/*
	ship->addComponent<Gun>();
	*/


	//ASTEROIDE DE PRUEBA

	Entity* testAsteroid = mngr->addEntity();
	testAsteroid->setGroup(_grp_ASTEROIDS);
	
	testAsteroid->addComponent<Transform>(Vector2D(100, 100), Vector2D(sdlutils().rand().nextInt(-1,1), sdlutils().rand().nextInt(-1, 1)) * 50, 50, 50, 0);
	testAsteroid->addComponent<ShowAtOppositeSide>();
	testAsteroid->addComponent<FramedImage>(Game::getTexture("AsteroidG"), 50, 6, 5);
	testAsteroid->addComponent<Follow>(ship->getComponent<Transform>());
	/*
	testAsteroid->addComponent<Generations>();
	*/

}

BattleState::~BattleState()
{
}
