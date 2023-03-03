#include "PauseState.h"
#include "../ecs/Entity.h"
#include "../components/Image.h"
#include "../components/Transform.h"
#include "Game.h"

PauseState::PauseState()
{
	std::cout << "Esta es la zona de pausa\n";
	auto color = SDL_Color();
	color.r = 0;
	color.g = 255;
	color.b = 0;
	color.a = 255;

	hitText = new Texture(SDLUtils::instance()->renderer(), "mikmikmikmik", sdlutils().fonts().at("ARIAL"), color);

	
	auto text = mngr->addEntity();
	text->addComponent<Transform>(Vector2D(WIN_WIDTH/2, WIN_HEIGHT/2), Vector2D(0,0), sdlutils().msgs().at("HitMSG").width(), sdlutils().msgs().at("HitMSG").height());
	text->addComponent<Image>(&sdlutils().msgs().at("HitMSG"));


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
	GameState::render();
	hitText->render(0, 0);
}


