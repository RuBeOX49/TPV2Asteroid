#pragma once
#include "GameState.h"
#include "Game.h"
#include "../sdlutils/SDLUtils.h"

class MultiplayerDefeatState : public GameState {
private:
	
	Texture* TextTexture1;
	Texture* TextTexture2;

public:

	MultiplayerDefeatState();
	~MultiplayerDefeatState() {
		delete TextTexture1;
		delete TextTexture2;
	}

};