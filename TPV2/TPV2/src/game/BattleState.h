#pragma once
#include "GameState.h"
#include "../sdlutils/SDLUtils.h"
class BattleState : public GameState
{
public:

	BattleState();
	~BattleState();

private:

	SoundEffect* soundTrack;
};
