#pragma once
#include "GameState.h"
#include "../sdlutils/SDLUtils.h"
class MultiplayerState : public GameState
{
public:

	Texture* waitingTexture;

	MultiplayerState();
	~MultiplayerState() {
		soundTrack->haltChannel();
		delete waitingTexture;
	}

private:

	SoundEffect* soundTrack;
};
