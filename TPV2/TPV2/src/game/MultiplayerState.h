#pragma once
#include "GameState.h"
#include "../sdlutils/SDLUtils.h"
class MultiplayerState : public GameState
{
public:

	Texture* waitingTexture;

	MultiplayerState();
	~MultiplayerState() {
		delete waitingTexture;
	}

private:

	SoundEffect* soundTrack;
};
