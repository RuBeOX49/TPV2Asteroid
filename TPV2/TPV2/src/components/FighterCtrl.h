#pragma once
#include "../ecs/Component.h"
#include "../components/Transform.h"
#include "../ecs/Entity.h"
#include "../sdlutils/SDLUtils.h"

class FighterCtrl : public Component {
private:
	SoundEffect* thrust;
	Transform* transform;
	int rotationFactor = 5;
	float shipSpeed = 10;

public:
	static const int id = _FIGHTERCTRL;

	FighterCtrl();
	~FighterCtrl() {}

	void initComponent();

	void setVel(float newVel);

	float getVel();

	float getRotationFactor();

	void playThrust();
};