#pragma once
#include "BattleState.h"
#include "PauseState.h"
#include "WinState.h"
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
	soundTrack = &sdlutils().soundEffects().at("Navesitas");
	soundTrack->play();
	Entity* background = mngr->addEntity();
	background->addComponent<Transform>(Vector2D(0, 0), Vector2D(), WIN_WIDTH, WIN_HEIGHT);
	background->addComponent<FramedImage>(Game::getTexture("Background"));

	//La Nave
	Entity* ship = mngr->addEntity();
	ship->setGroup(_grp_FIGHTER);
	ship->addComponent<Transform>(Vector2D(WIN_WIDTH / 2, WIN_HEIGHT / 2), Vector2D(), 100, 100, 0);
	ship->addComponent<HealthComponent>();
	ship->addComponent<DeAcceleration>();
	ship->addComponent<FramedImage>(Game::getTexture("Ship"));
	ship->addComponent<FighterCtrl>();
	ship->addComponent<ShowAtOppositeSide>();
	ship->addComponent<Gun>();
	
	astMngr = new AsteroidsManager(mngr, ship);
	collMngr = new CollisonsManager(mngr, astMngr);

	astMngr->createAsteroid(10);

}

BattleState::~BattleState()
{
	soundTrack->haltChannel();
	delete collMngr;
	delete astMngr;
}

void BattleState::update()
{
	GameState::update();
	collMngr->handlePhysics();
	astMngr->addAsteroidFrequently();
	if (astMngr->getAsteroids() == 0)
		GameStateMachine::instance()->changeState(new WinState());
}

void BattleState::handleInput()
{
	GameState::handleInput();
	if (InputHandler::instance()->isKeyDown(SDLK_SPACE)) {
		GameStateMachine::instance()->pushState(new PauseState());
	}


}
