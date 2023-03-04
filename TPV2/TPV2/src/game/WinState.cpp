#include "WinState.h"

WinState::WinState() {

}


void WinState::handleInput() {

	if (InputHandler::instance()->isKeyDown(SDLK_SPACE))
	{
		GameStateMachine::instance()->changeState(new BattleState());
	}
}