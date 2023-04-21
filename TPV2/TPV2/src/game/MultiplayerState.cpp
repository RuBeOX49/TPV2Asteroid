#include "MultiplayerState.h"
#include "Game.h"
#include "../systems/NetSystem.h"

MultiplayerState::MultiplayerState()
{
	
	Game::instance()->addSystem<NetSystem>();




}

MultiplayerState::~MultiplayerState()
{
}
