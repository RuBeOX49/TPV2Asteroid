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
	Vector2D pos = Vector2D(WIN_WIDTH / 2 - hitText->width(), WIN_HEIGHT / 2 - hitText->height());
	auto origin = Vector2D(0, 0);
	SDL_Rect src = build_sdlrect(origin, hitText->width(), hitText->height());
	
	
	SDL_Rect juanAlberto = build_sdlrect(pos, hitText->width() * 10, hitText->height() * 10);
	hitText->render(src, juanAlberto);
}
