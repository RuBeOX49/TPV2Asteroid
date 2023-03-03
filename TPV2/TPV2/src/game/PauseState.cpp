#include "PauseState.h"
#include "../ecs/Entity.h"


PauseState::PauseState()
{
	hitText = &sdlutils().msgs().at("HitMSG");
	
	auto text = mngr->addEntity();



}

void PauseState::handleInput()
{
	GameState::handleInput();

	if (InputHandler::instance()->isKeyDown(SDLK_SPACE))
	{
		Game::instance()->resumeGame();
	}
}

void PauseState::render() const
{
	
}
