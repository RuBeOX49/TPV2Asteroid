#pragma once
#include "../ecs/Component.h"
#include "../sdlutils/Texture.h"


struct FramedImage : public Component
{
public:

	bool animated;

	Texture* texture;

	double timer = 0.0;

	double stepDuration;
	

	int frameColumn = 0;
	int frameRow = 0;

	int columns;
	int rows;


	static const int id = _IMAGE;

	FramedImage(Texture* texture, double stepDuration = 1.0, int columns = 1, int rows = 1, bool animated = false);
	~FramedImage();

};