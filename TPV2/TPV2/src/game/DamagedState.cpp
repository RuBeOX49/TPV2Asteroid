#pragma once
#include "DamagedState.h"

DamagedState::DamagedState()
{
	std::cout << "Estas en DamagedState\n";
}

void DamagedState::handleInput()
{
	GameState::handleInput();

	if (InputHandler::instance()->isKeyDown(SDLK_SPACE))
	{
		Game::instance()->resumeGame();
	}
}
