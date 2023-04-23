#include "MultiplayerState.h"
#include "Game.h"
#include "../systems/NetSystem.h"
#include "../components/Transform.h"
#include "../components/FramedImage.h"

MultiplayerState::MultiplayerState()
{
	

	soundTrack = &sdlutils().soundEffects().at("Navesitas");
	soundTrack->play();
	Entity* background = mngr->addEntity();
	mngr->addComponent<Transform>(background, Vector2D(0, 0), Vector2D(), WIN_WIDTH, WIN_HEIGHT);
	mngr->addComponent<FramedImage>(background, Game::getTexture("Background"));

	//Waiting for other player
	waitingTexture = new Texture(SDLUtils::instance()->renderer(), "PAUSA. Pulsa Space para seguir.", *(Game::instance()->getGameFont()), build_sdlcolor("0x2020ffff"));

	auto text = mngr->addEntity();
	mngr->addComponent<Transform>(text, Vector2D(WIN_WIDTH / 2 - waitingTexture->width() / 2, waitingTexture->height() + 100), Vector2D(0, 0), waitingTexture->width(), waitingTexture->height());
	mngr->addComponent<FramedImage>(text, waitingTexture);

	Game::instance()->addSystem<NetSystem>();

	//Not waiting anymore
	text->setAlive(false);

}

