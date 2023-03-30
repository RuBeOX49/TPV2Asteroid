#pragma once
#include "DamagedState.h"
#include "../ecs/Entity.h"
#include "../components/Image.h"
#include "../components/Transform.h"
#include "Game.h"
#include "../sdlutils/SDLUtils.h"

DamagedState::DamagedState()
{

	textTexture1 = new Texture(SDLUtils::instance()->renderer(), "Te han golpeado!", *(Game::instance()->getGameFont()), build_sdlcolor("0x2020ffff"));
	textTexture2 = new Texture(SDLUtils::instance()->renderer(), " Pulsa Space para seguir.", *(Game::instance()->getGameFont()), build_sdlcolor("0x2020ffff"));

	auto text1 = mngr->addEntity();
	mngr->addComponent<Transform>(text1, Vector2D(WIN_WIDTH / 2 - textTexture1->width() / 2, WIN_HEIGHT / 2 - textTexture1->height() / 2), Vector2D(0, 0), textTexture1->width(), textTexture1->height());
	mngr->addComponent<Image>(text1, textTexture1);


	auto text2 = mngr->addEntity();
	mngr->addComponent<Transform>(text2, Vector2D(WIN_WIDTH / 2 - textTexture2->width() / 2, WIN_HEIGHT / 2 - textTexture2->height() / 2 + textTexture1->height()), Vector2D(0, 0), textTexture2->width(), textTexture2->height());
	mngr->addComponent<Image>(text2, textTexture2);
}

void DamagedState::handleInput()
{
	GameState::handleInput();

	if (InputHandler::instance()->isKeyDown(SDLK_SPACE))
	{
		Game::instance()->resumeGame();
	}
}
