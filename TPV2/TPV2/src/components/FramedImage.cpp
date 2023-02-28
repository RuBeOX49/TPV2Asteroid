#include "FramedImage.h"
#include "../ecs/Entity.h"
#include "Transform.h"
#include "../sdlutils/SDLUtils.h"

FramedImage::FramedImage(Texture* texture, Uint32 stepDuration, int columns, int rows):
	texture(texture), stepDuration(stepDuration), columns(columns), rows(rows)
{
	lastFrameShift = sdlutils().currRealTime();
}

FramedImage::~FramedImage()
{
}

void FramedImage::update()
{
	if (sdlutils().currRealTime() - lastFrameShift <= stepDuration) {
		lastFrameShift += stepDuration;

		frameColumn++;

		if( frameColumn == columns)
		{
			frameColumn = 0;
			frameRow++;
			frameRow %= rows;
		}
	}
}
void FramedImage::render() const
{
	SDL_Rect sourceRect = build_sdlrect(frameColumn * texture->width() / columns, frameRow * texture->height() / rows, texture->width() / columns,texture->height() / rows);
	SDL_Rect destRect = ent->getComponent<Transform>()->getRect();
	texture->render(sourceRect, destRect);
}
