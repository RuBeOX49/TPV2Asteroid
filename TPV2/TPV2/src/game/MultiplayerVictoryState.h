#pragma once
#include "GameState.h"
#include "Game.h"
#include "../sdlutils/SDLUtils.h"

class MultiplayerVictoryState : public GameState {
private:

	Texture* TextTexture1;
	Texture* TextTexture2;

public:

	MultiplayerVictoryState();
	~MultiplayerVictoryState() {
		delete TextTexture1;
		delete TextTexture2;
	}

};