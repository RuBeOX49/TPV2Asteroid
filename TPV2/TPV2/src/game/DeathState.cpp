#include "DeathState.h"

DeathState::DeathState()
{
	std::cout << "Est�s en la DeathState\n";
}

void DeathState::handleInput()
{
	GameState::handleInput();

	if (InputHandler::instance()->isKeyDown(SDLK_SPACE))
	{
		Game::instance()->resumeGame();
	}
}
