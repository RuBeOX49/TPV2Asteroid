#pragma once
#include "GameState.h"
#include "Game.h"
#include "../sdlutils/SDLUtils.h"

class DamagedState : public GameState {
private:

	Texture* textTexture1;
	Texture* textTexture2;


public:

	DamagedState();
	~DamagedState() {
	
		delete textTexture1;
		delete textTexture2;

	}


};