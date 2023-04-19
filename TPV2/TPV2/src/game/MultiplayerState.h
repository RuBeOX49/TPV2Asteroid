#pragma once
#include "GameState.h"
#include "../sdlutils/SDLUtils.h"
class MultiplayerState : public GameState
{
public:

	MultiplayerState();
	~MultiplayerState();

private:

	SoundEffect* soundTrack;
};
