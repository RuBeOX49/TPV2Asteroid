#include "MainMenuState.h"
#include "../ecs/Entity.h"
#include "../components/FramedImage.h"
#include "../components/Transform.h"
#include "Game.h"
#include "../sdlutils/SDLUtils.h"


MainMenuState::MainMenuState()
{
	TextTexture = new Texture(SDLUtils::instance()->renderer(), "Pulsa SPACE para 1 jugador", *(Game::instance()->getGameFont()), build_sdlcolor("0x2020ffff"));

	auto text = mngr->addEntity();
	text->setGroup(_grp_UI);
	mngr->addComponent<Transform>(text, Vector2D(WIN_WIDTH / 2 - TextTexture->width() / 2, WIN_HEIGHT / 2 - TextTexture->height() / 2), Vector2D(0, 0), TextTexture->width(), TextTexture->height());
	mngr->addComponent<FramedImage>(text, TextTexture);


	P2Texture = new Texture(SDLUtils::instance()->renderer(), "Pulsa C para 2 jugadores", *(Game::instance()->getGameFont()), build_sdlcolor("0x2020ffff"));

	auto text2 = mngr->addEntity();
	text2->setGroup(_grp_UI);
	mngr->addComponent<Transform>(text2, Vector2D(WIN_WIDTH / 2 - P2Texture->width() / 2, WIN_HEIGHT / 2 - P2Texture->height() * 3 / 2), Vector2D(0, 0), P2Texture->width(), P2Texture->height());
	mngr->addComponent<FramedImage>(text2, P2Texture);
}
