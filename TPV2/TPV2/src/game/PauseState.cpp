#include "PauseState.h"

PauseState::PauseState()
{
	hitText = &sdlutils().msgs().at("HitMSG");
}

void PauseState::handleInput()
{
	if (InputHandler::instance()->isKeyDown(SDLK_SPACE))
	{
		Game::instance()->resumeGame();
	}
}

void PauseState::render() const
{
	hitText->render(WIN_WIDTH / 2 - hitText->width(), WIN_HEIGHT / 2 - hitText->height());
}
