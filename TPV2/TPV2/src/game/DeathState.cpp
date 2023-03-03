#include "DeathState.h"
#include "BattleState.h"

DeathState::DeathState()
{
	std::cout << "Estás en la DeathState\n";
}

void DeathState::handleInput()
{
	GameState::handleInput();

	if (InputHandler::instance()->isKeyDown(SDLK_SPACE))
	{
		GameStateMachine::instance()->changeState(new BattleState());
	}
}
