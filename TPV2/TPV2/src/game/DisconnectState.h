#pragma once
#include "GameState.h"
#include "Game.h"
#include "../sdlutils/SDLUtils.h"

class DisconnectState : public GameState {
private:

	Texture* TextTexture1;
	Texture* TextTexture2;

public:

	DisconnectState();
	~DisconnectState() {
		delete TextTexture1;
		delete TextTexture2;
	}

};