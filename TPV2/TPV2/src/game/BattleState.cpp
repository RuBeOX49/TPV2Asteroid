#pragma once
#include "BattleState.h"
#include "PauseState.h"
#include "WinState.h"
#include "../ecs/Entity.h"
#include "Game.h"
#pragma region allComponents
#include "../components/DeAcceleration.h"
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

	Game::instance()->send(Message(_m_BATTLE_STATE_SETUP), true);

}

BattleState::~BattleState()
{
	soundTrack->haltChannel();
}


