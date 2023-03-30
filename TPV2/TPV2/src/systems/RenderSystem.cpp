#include "RenderSystem.h";
#include "../game/Game.h"
#include "../ecs/Entity.h"
#include "../components/FramedImage.h"
#include "../components/Transform.h"

void RenderSystem::initSystem() {

}

void RenderSystem::receive(const Message& m) {

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
		auto fIm = mngr_->getComponent<FramedImage>(var);

		SDL_Rect sourceRect = build_sdlrect(fIm->frameColumn * fIm->texture->width() / fIm->columns, fIm->frameRow * fIm->texture->height() / fIm->rows, fIm->texture->width() / fIm->columns, fIm->texture->height() / fIm->rows);
		SDL_Rect destRect = mngr_->getComponent<Transform>(var)->getRect();
		fIm->texture->render(sourceRect, destRect);
	}
}
void RenderSystem::onRoundStart()
{
}

void RenderSystem::onRoundOver()
{
}

void RenderSystem::onGameStart()
{
}

void RenderSystem::onGameOver()
{
}
