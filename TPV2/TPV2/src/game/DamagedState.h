#pragma once
#include "GameState.h"
#include "Game.h"
#include "../sdlutils/SDLUtils.h"

class DamagedState : public GameState {
private:


public:

	DamagedState();
	~DamagedState() {}

	virtual void handleInput();
};