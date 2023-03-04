#pragma once
#include "GameState.h"
#include "../sdlutils/InputHandler.h"
#include "GameStateMachine.h"
#include "BattleState.h"
class WinState: public GameState
{
private:


public:
	WinState();

	virtual void handleInput();
};

