#pragma once
#include "../ecs/Component.h"


class FramedImage : public Component
{
private:

	Texture* texture;
	Uint32 stepDuration;


public:

	FramedImage(Texture* texture, Uint32 stepDuration);
	~FramedImage();
};