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
#include "../components/Transform.h"
#pragma endregion



BattleState::BattleState()
{
	soundTrack = &sdlutils().soundEffects().at("Navesitas");
	soundTrack->play();
	Entity* background = mngr->addEntity();
	mngr->addComponent<Transform>(background, Vector2D(0, 0), Vector2D(), WIN_WIDTH, WIN_HEIGHT);
	mngr->addComponent<FramedImage>(background, Game::getTexture("Background"));

	//La Nave
	Entity* ship = mngr->addEntity();
	ship->setGroup(_grp_FIGHTER);
	mngr->addComponent<Transform>(ship, Vector2D(WIN_WIDTH / 2, WIN_HEIGHT / 2), Vector2D(), 100, 100, 0);
	mngr->addComponent<HealthComponent>(ship);
	mngr->addComponent<DeAcceleration>(ship);
	mngr->addComponent<FramedImage>(ship, Game::getTexture("Ship"));
	mngr->addComponent<FighterCtrl>(ship);
	mngr->addComponent<Gun>(ship);
	


	



	Game::instance()->send(Message(_m_BATTLE_STATE_SETUP), true);

}

BattleState::~BattleState()
{
	soundTrack->haltChannel();
}


