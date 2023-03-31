#include "PauseState.h"
#include "../ecs/Entity.h"
#include "../components/FramedImage.h"
#include "../components/Transform.h"
#include "Game.h"
#include "../sdlutils/SDLUtils.h"

PauseState::PauseState()
{
	
	TextTexture = new Texture(SDLUtils::instance()->renderer(), "PAUSA. Pulsa Space para seguir.", *(Game::instance()->getGameFont()), build_sdlcolor("0x2020ffff"));

	auto text = mngr->addEntity();
	mngr->addComponent<Transform>(text, Vector2D(WIN_WIDTH/2 - TextTexture->width()/2, WIN_HEIGHT/2 - TextTexture->height() / 2), Vector2D(0,0), TextTexture->width(), TextTexture->height());
	mngr->addComponent<FramedImage>(text, TextTexture);


}






