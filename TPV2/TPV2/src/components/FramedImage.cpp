#include "FramedImage.h"
#include "../ecs/Entity.h"
#include "Transform.h"
#include "../sdlutils/SDLUtils.h"
#include "../game/Game.h"

FramedImage::FramedImage(Texture* texture, double stepDuration, int columns, int rows, bool animated):
	texture(texture), stepDuration(stepDuration), columns(columns), rows(rows), animated(animated) {}

FramedImage::~FramedImage() {}





