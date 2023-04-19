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
	

}
void RenderSystem::onRoundStart()
{
	currHealth = STARTING_HEALTH;
}


