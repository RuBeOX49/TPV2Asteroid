#pragma once
#include "GameState.h"
#include "../sdlutils/InputHandler.h"
#include "GameStateMachine.h"
#include "BattleState.h"
class WinState: public GameState
{
private:
	Texture* textTexture1;
	Texture* textTexture2;

public:
	WinState();
	~WinState();


	virtual void handleInput();
};

