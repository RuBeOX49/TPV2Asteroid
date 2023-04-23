#include "MultiplayerDefeatState.h"
#include "../ecs/Entity.h"
#include "../components/FramedImage.h"
#include "../components/Transform.h"
#include "Game.h"
#include "../sdlutils/SDLUtils.h"


MultiplayerDefeatState::MultiplayerDefeatState()
{
	TextTexture1 = new Texture(SDLUtils::instance()->renderer(), "Has perdido...", *(Game::instance()->getGameFont()), build_sdlcolor("0x2020ffff"));
	TextTexture2 = new Texture(SDLUtils::instance()->renderer(), "Pulsa Space para volver al menu principal.", *(Game::instance()->getGameFont()), build_sdlcolor("0x2020ffff"));

	auto text = mngr->addEntity();
	mngr->addComponent<Transform>(text, Vector2D(WIN_WIDTH / 2 - TextTexture1->width() / 2, WIN_HEIGHT / 2 - TextTexture1->height() / 2), Vector2D(0, 0), TextTexture1->width(), TextTexture1->height());
	mngr->addComponent<FramedImage>(text, TextTexture1);

	auto text2 = mngr->addEntity();
	mngr->addComponent<Transform>(text2, Vector2D(WIN_WIDTH / 2 - TextTexture2->width() / 2, WIN_HEIGHT / 2 - TextTexture2->height() / 2 + TextTexture1->height()), Vector2D(0, 0), TextTexture2->width(), TextTexture2->height());
	mngr->addComponent<FramedImage>(text2, TextTexture2);


}