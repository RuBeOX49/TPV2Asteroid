#include "MultiplayerState.h"
#include "Game.h"
#include "../systems/NetSystem.h"
#include "../components/Transform.h"
#include "../components/FramedImage.h"

MultiplayerState::MultiplayerState()
{
	
	Game::instance()->addSystem<NetSystem>();

	soundTrack = &sdlutils().soundEffects().at("Navesitas");
	soundTrack->play();
	Entity* background = mngr->addEntity();
	mngr->addComponent<Transform>(background, Vector2D(0, 0), Vector2D(), WIN_WIDTH, WIN_HEIGHT);
	mngr->addComponent<FramedImage>(background, Game::getTexture("Background"));

}

MultiplayerState::~MultiplayerState()
{
}
