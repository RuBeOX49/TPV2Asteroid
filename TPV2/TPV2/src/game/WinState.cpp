#include "WinState.h"
#include "BattleState.h"
#include "../ecs/Entity.h"
#include "../components/FramedImage.h"
#include "../components/Transform.h"
#include "Game.h"
#include "../sdlutils/SDLUtils.h"

WinState::WinState() {

	textTexture1 = new Texture(SDLUtils::instance()->renderer(), "Felicidades, has ganado!", *(Game::instance()->getGameFont()), build_sdlcolor("0x2020ffff"));
	textTexture2 = new Texture(SDLUtils::instance()->renderer(), " Pulsa Space para reiniciar el juego.", *(Game::instance()->getGameFont()), build_sdlcolor("0x2020ffff"));

	auto text1 = mngr->addEntity();
	text1->setGroup(_grp_UI);
	mngr->addComponent<Transform>(text1, Vector2D(WIN_WIDTH / 2 - textTexture1->width() / 2, WIN_HEIGHT / 2 - textTexture1->height() / 2), Vector2D(0, 0), textTexture1->width(), textTexture1->height());
	mngr->addComponent<FramedImage>(text1, textTexture1);


	auto text2 = mngr->addEntity();
	text2->setGroup(_grp_UI);
	mngr->addComponent<Transform>(text2, Vector2D(WIN_WIDTH / 2 - textTexture2->width() / 2, WIN_HEIGHT / 2 - textTexture2->height() / 2 + textTexture1->height()), Vector2D(0, 0), textTexture2->width(), textTexture2->height());
	mngr->addComponent<FramedImage>(text2, textTexture2);

}

WinState::~WinState()
{
	delete textTexture1;
	delete textTexture2;

}


void WinState::handleInput() {

	if (InputHandler::instance()->isKeyDown(SDLK_SPACE))
	{
		GameStateMachine::instance()->changeState(new BattleState());
	}
}