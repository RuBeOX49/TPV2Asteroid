#include "SceneCtrlSystem.h"
#include "../game/Game.h"
#include "../game/GameStateMachine.h"
#include "../game/DeathState.h"
#include "../game/DamagedState.h"
#include "../game/PauseState.h"
#include "../game/BattleState.h"
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
	default:
		break;
	}
}

void SceneCtrlSystem::initSystem()
{
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
			
			m.id = _m_CHANGE_STATE;
			m.new_state_ID.state = state_BATTLE;

			Game::instance()->send(m, true);
			GameStateMachine::instance()->changeState(new BattleState());
			
			break;
		default:
			std::cout << "state_ sin definir\n";
			break;
		}
		


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
		Game::instance()->setAllSystemsContext();
	}
	else {

		m.id = _m_CHANGE_STATE;
		m.new_state_ID.state = state_DAMAGED;

		GameStateMachine::instance()->pushState(new DamagedState());
		Game::instance()->setAllSystemsContext();
	}
}

void SceneCtrlSystem::onAsteroidsExtinction()
{
}
