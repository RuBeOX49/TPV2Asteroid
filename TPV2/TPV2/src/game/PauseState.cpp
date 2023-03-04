#include "PauseState.h"
#include "../ecs/Entity.h"
#include "../components/Image.h"
#include "../components/Transform.h"
#include "Game.h"
#include "../sdlutils/SDLUtils.h"

PauseState::PauseState()
{
	std::cout << "Esta es la zona de pausa\n";

	auto textSource = Font("resources/fonts/NES-Chimera.ttf", 20);
	auto color = SDL_Color();
	color.r = 255;
	color.g = 0;
	color.b = 0;
	color.a = 255;

	hitText = new Texture(SDLUtils::instance()->renderer(), "mikmikmikmik", textSource, build_sdlcolor("0xff00ffff"));

	
	auto text = mngr->addEntity();
	text->addComponent<Transform>(Vector2D(WIN_WIDTH/2, WIN_HEIGHT/2), Vector2D(0,0), hitText->width(), hitText->height());
	text->addComponent<Image>(hitText);


}

void PauseState::handleInput()
{
	GameState::handleInput();

	if (InputHandler::instance()->isKeyDown(SDLK_SPACE))
	{
		Game::instance()->resumeGame();
	}
}




