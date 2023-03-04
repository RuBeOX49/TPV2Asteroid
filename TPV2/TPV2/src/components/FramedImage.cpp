#include "FramedImage.h"
#include "../ecs/Entity.h"
#include "Transform.h"
#include "../sdlutils/SDLUtils.h"
#include "../game/Game.h"

FramedImage::FramedImage(Texture* texture, double stepDuration, int columns, int rows):
	texture(texture), stepDuration(stepDuration), columns(columns), rows(rows) {}

FramedImage::~FramedImage() {}

//Calcula el tiempo pasado desde la ultima vez que se cambio el frame, y determina si es hora de volverlo a cambiar
void FramedImage::update()
{
	if (timer >= stepDuration) {
		timer -= stepDuration;

		frameColumn++;

		if( frameColumn == columns)
		{
			frameColumn = 0;
			frameRow++;
			frameRow %= rows;
		}
	}
	timer += Game::instance()->getDeltaTime();
}

//Renderiza el frame determinado
void FramedImage::render() const
{
	SDL_Rect sourceRect = build_sdlrect(frameColumn * texture->width() / columns, frameRow * texture->height() / rows, texture->width() / columns,texture->height() / rows);
	SDL_Rect destRect = ent->getComponent<Transform>()->getRect();
	texture->render(sourceRect, destRect);
}



