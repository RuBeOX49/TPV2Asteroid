#include "SceneCtrlSystem.h"
#include "../game/Game.h"
#include "../game/GameStateMachine.h"
#include "../game/DeathState.h"
#include "../game/WinState.h"
#include "../game/DamagedState.h"
#include "../game/PauseState.h"
#include "../game/BattleState.h"
#include "../game/MultiplayerState.h"
#include "../sdlutils/InputHandler.h"


void SceneCtrlSystem::receive(const Message& m)
{
	switch (m.id)
	{
	case _m_BATTLE_STATE_SETUP:
		state_ = state_BATTLE;
		break;
	case _m_CHANGE_STATE:
		state_ = m.new_state_ID.state;
		break;
	case _m_COLLISION_AST_SHIP:
		onCollision_FighterAsteroid(m.remainingHealth);
		break;
	case _m_ASTEROIDS_EXTINCTION:
		onAsteroidsExtinction();
		break;
	case _m_SETUP_MULTIPLAYER:
		setupMultiplayer(m.isHost);
		break;
	default:
		break;
	}
}

void SceneCtrlSystem::initSystem()
{
	state_ = state_MAINMENU;
}

void SceneCtrlSystem::update()
{

	if (InputHandler::instance()->isKeyDown(SDLK_SPACE)) {

		Message m;
		
		switch (state_)
		{
		case state_BATTLE:
			m.id = _m_CHANGE_STATE;
			m.new_state_ID.state = state_PAUSED;

			Game::instance()->send(m, true);
			GameStateMachine::instance()->pushState(new PauseState());
			
			break;
		case state_PAUSED:
		case state_DAMAGED:
			
			m.id = _m_CHANGE_STATE;
			m.new_state_ID.state = state_BATTLE;

			Game::instance()->send(m, true);
			GameStateMachine::instance()->popState();
			
			break;
		case state_DEAD:
		case state_WIN:
		case state_MAINMENU:
			
			m.id = _m_BATTLE_RESTART;
			m.new_state_ID.state = state_BATTLE;

			Game::instance()->send(m, true);
			GameStateMachine::instance()->changeState(new BattleState());
			
			break;
		default:
			std::cout << "state_ sin definir\n";
			break;
		}
		


	}

	if (state_ == state_MAINMENU && InputHandler::instance()->isKeyDown(SDLK_c)) {
		
		Message m;

		m.id = _m_CHANGE_STATE;
		m.new_state_ID.state = state_MULTIPLAYER;

		Game::instance()->send(m, true);
		GameStateMachine::instance()->changeState(new MultiplayerState());
	
	}




}

void SceneCtrlSystem::onCollision_FighterAsteroid(int remainingHealth)
{
	Message m;

	if (remainingHealth == 0) {

		m.id = _m_CHANGE_STATE;
		m.new_state_ID.state = state_DEAD;

		Game::instance()->send(m);
		GameStateMachine::instance()->changeState(new DeathState());
	}
	else {

		m.id = _m_CHANGE_STATE;
		m.new_state_ID.state = state_DAMAGED;

		Game::instance()->send(m);
		GameStateMachine::instance()->pushState(new DamagedState());
	}
}

void SceneCtrlSystem::onAsteroidsExtinction()
{
	Message m;

	m.id = _m_CHANGE_STATE;
	m.new_state_ID.state = state_WIN;

	Game::instance()->send(m);
	GameStateMachine::instance()->changeState(new WinState());
}

void SceneCtrlSystem::setupMultiplayer(bool isHost)
{

}
