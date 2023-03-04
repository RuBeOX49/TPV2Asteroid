#pragma once
#include "GameState.h"
#include "Game.h"
#include "../sdlutils/SDLUtils.h"

class DeathState : public GameState {
private:

	Texture* textTexture1;
	Texture* textTexture2;

public:

	DeathState();
	~DeathState() {
	
		delete textTexture1;
		delete textTexture2;

	}

	virtual void handleInput();
};
