#pragma once
#include "GameState.h"
#include "Game.h"
#include "../sdlutils/SDLUtils.h"

class PauseState : public GameState {
private:

	Texture* hitText;

public:

	PauseState();
	~PauseState() {
		delete hitText;
	}

	virtual void handleInput();
	virtual void render() const;
};