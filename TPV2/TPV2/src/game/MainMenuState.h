#pragma once
#include "GameState.h"
#include "Game.h"
#include "../sdlutils/SDLUtils.h"

class MainMenuState : public GameState {
private:

	Texture* TextTexture;
	Texture* P2Texture;

public:

	MainMenuState();
	~MainMenuState() {
		delete TextTexture;
		delete P2Texture;
	}

};