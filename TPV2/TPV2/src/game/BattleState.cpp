#pragma once
#include "BattleState.h"
#include "PauseState.h"
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
	collMngr = new CollisonsManager(mngr);
	//LA NAVE
	Entity* ship = mngr->addEntity();
	ship->setGroup(_grp_FIGHTER);
	ship->addComponent<Transform>(Vector2D(WIN_WIDTH / 2, WIN_HEIGHT / 2), Vector2D(), 100, 100, 0);
	ship->addComponent<HealthComponent>();
	ship->addComponent<DeAcceleration>();
	ship->addComponent<Image>(Game::getTexture("Ship"));
	ship->addComponent<FighterCtrl>();
	ship->addComponent<ShowAtOppositeSide>();
	ship->addComponent<Gun>();
	
	astMngr = new AsteroidsManager(mngr, ship);

}

BattleState::~BattleState()
{
	delete collMngr;
}

void BattleState::update()
{
	GameState::update();
	collMngr->handlePhysics();
	astMngr->addAsteroidFrequently();
}

void BattleState::handleInput()
{
	GameState::handleInput();
	if (InputHandler::instance()->isKeyDown(SDLK_SPACE)) {
		std::cout << "se llama\n";
		GameStateMachine::instance()->pushState(new PauseState());
	}


}
