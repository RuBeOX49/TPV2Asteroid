#pragma once
#include "../ecs/Component.h"
#include "../sdlutils/Texture.h"


class FramedImage : public Component
{
private:

	Texture* texture;

	double timer = 0.0;

	double stepDuration;
	

	int frameColumn = 0;
	int frameRow = 0;

	int columns;
	int rows;

public:

	static const int id = _IMAGE;

	FramedImage(Texture* texture, double stepDuration, int columns, int rows);
	~FramedImage();

	virtual void update();
	virtual void render() const;
};