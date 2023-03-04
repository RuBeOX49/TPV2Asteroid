#pragma once
#include "GameState.h"
#include "Game.h"
#include "../sdlutils/SDLUtils.h"

class PauseState : public GameState {
private:

	Texture* TextTexture;

public:
	
	PauseState();
	~PauseState() {
		delete TextTexture;
	}

	virtual void handleInput();
};