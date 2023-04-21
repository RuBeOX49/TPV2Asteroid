#include "MultiplayerState.h"
#include "Game.h"
#include "../systems/NetSystem.h"

MultiplayerState::MultiplayerState()
{
	
	

	//realizar la conexion
	while (!Game::instance()->getSystem<NetSystem>()->connect())
		;




}

MultiplayerState::~MultiplayerState()
{
}
