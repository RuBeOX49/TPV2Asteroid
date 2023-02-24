#pragma once
#include "../ecs/Component.h"
#include "../components/Transform.h"
#include "../ecs/Entity.h"

class FighterCtrl : public Component {
private:
	Transform* transform;
	float shipSpeed=0;

public:
	static const int id = _FIGHTERCTRL;

	FighterCtrl();
	~FighterCtrl();

	void initComponent();

	void handleInput();

	void setVel(int newVel);
};