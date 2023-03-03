#include "PauseState.h"
#include "../ecs/Entity.h"
#include "../components/Image.h"
#include "../components/Transform.h"

PauseState::PauseState()
{
	std::cout << "Esta es la zona de pausa\n";
	
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


