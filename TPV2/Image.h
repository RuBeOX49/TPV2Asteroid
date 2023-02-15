#pragma once
#include "Component.h"
#include "../TPV2/src/sdlutils/Texture.h"
#include "GameObject.h"
#include "Transform.h"
class Image : public Component
{
private:
	Transform* transform;
	Texture* texture;

public:
	static const int id = _IMAGE;
	Image(Texture* texture) :texture(texture), transform(nullptr) {};
	void initComponent();
	void render();
};

