#pragma once
#include "GameState.h"
#include "Game.h"
#include "../sdlutils/SDLUtils.h"

class DeathState : public GameState {
private:


public:

	DeathState();
	~DeathState() {}

	virtual void handleInput();
};
