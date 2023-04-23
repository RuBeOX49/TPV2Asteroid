#include "RenderSystem.h";
#include "../game/Game.h"
#include "../ecs/Entity.h"
#include "../components/FramedImage.h"
#include "../components/Transform.h"

void RenderSystem::initSystem() {
	healthTexture = Game::getTexture("Heart");
	state_ = state_MAINMENU;
}

void RenderSystem::receive(const Message& m) {
	switch (m.id)
	{
	case _m_BATTLE_STATE_SETUP:
		
		onRoundStart();
		break;
	case _m_COLLISION_AST_SHIP:
		currHealth = m.remainingHealth;
		break;
	case _m_CHANGE_STATE:
	case _m_BATTLE_RESTART:
		state_ = m.new_state_ID.state;
		break;
	case _m_SETUP_MULTIPLAYER:
		setupMultiplayer(m.name, m.enemyName, m.isHost);
		break;
	default:
		break;
	}
}

void RenderSystem::update() {

 	for (auto var : mngr_->getEntities())
	{
		auto fIm = mngr_->getComponent<FramedImage>(var);

		if (fIm->animated) {
			if (fIm->timer >= fIm->stepDuration) {
				fIm->timer -= fIm->stepDuration;

				fIm->frameColumn++;

				if (fIm->frameColumn == fIm->columns)
				{
					fIm->frameColumn = 0;
					fIm->frameRow++;
					fIm->frameRow %= fIm->rows;
				}
			}
			fIm->timer += Game::instance()->getDeltaTime();
		}
	
		

	}
}

void RenderSystem::render() const
{
	for (auto var : mngr_->getEntities())
	{
		if (var->getGroup() == _grp_UI || state_ != state_MAINMENU) {

		auto fIm = mngr_->getComponent<FramedImage>(var);

		SDL_Rect sourceRect = build_sdlrect(fIm->frameColumn * fIm->texture->width() / fIm->columns, fIm->frameRow * fIm->texture->height() / fIm->rows, fIm->texture->width() / fIm->columns, fIm->texture->height() / fIm->rows);
		SDL_Rect destRect = mngr_->getComponent<Transform>(var)->getRect();
		fIm->texture->render(sourceRect, destRect, mngr_->getComponent<Transform>(var)->rotation_);
		
		}
	}

	if (state_ == state_BATTLE)
	{
		for (int i = 0; i < currHealth; i++)
		{
			SDL_Rect rect = build_sdlrect(20 + i * (20 + 10), 20, 20, 20);
			healthTexture->render(rect);
		}
	}

	if (multiplayer) {
		//name
		Vector2D pos = fighterTransform->getPos() + Vector2D(-nameTexture->width() / 2, fighterTransform->getHeight());
		SDL_Rect rect = build_sdlrect(pos,nameTexture->width(),nameTexture->height());
		nameTexture->render(rect);

		//enemyName
		
		Vector2D enemypos = enemyFighterTransform->getPos() + Vector2D(-enemyNameTexture->width() / 2, enemyFighterTransform->getHeight());
		SDL_Rect rect2 = build_sdlrect(enemypos, enemyNameTexture->width(), enemyNameTexture->height());
		enemyNameTexture->render(rect2);

	}
	

}
void RenderSystem::onRoundStart()
{
	currHealth = STARTING_HEALTH;
}

void RenderSystem::setupMultiplayer(string name, string enemyName, bool isHost)
{
	//findFighters
	for (auto var : mngr_->getEntities()) {
		if (mngr_->groupId(var) == _grp_FIGHTER) {
			fighterTransform = mngr_->getComponent<Transform>(var);
		}
		if (mngr_->groupId(var) == _grp_ENEMY_FIGHTER) {
			enemyFighterTransform = mngr_->getComponent<Transform>(var);
		}
	}

	if (nameTexture != nullptr) {
		delete nameTexture;
		nameTexture = nullptr;
	}
	
	if (enemyNameTexture != nullptr) {
		delete enemyNameTexture;
		enemyNameTexture = nullptr;
	}

	//create textures
	nameTexture = new Texture(SDLUtils::instance()->renderer(), name, *(Game::instance()->getGameFont()), build_sdlcolor("0x2020ffff"));
	enemyNameTexture = new Texture(SDLUtils::instance()->renderer(), enemyName, *(Game::instance()->getGameFont()), build_sdlcolor("0x2020ffff"));

	multiplayer = true;

}


