#pragma once
#include "../ecs/Component.h"
#include "../sdlutils/Texture.h"


class FramedImage : public Component
{
private:

	Texture* texture;

	Uint32 stepDuration;
	Uint32 lastFrameShift = 0;

	int frameColumn = 0;
	int frameRow = 0;

	int columns;
	int rows;

public:

	static const int id = _IMAGE;

	FramedImage(Texture* texture, Uint32 stepDuration, int columns, int rows);
	~FramedImage();

	virtual void update();
	virtual void render() const;
};