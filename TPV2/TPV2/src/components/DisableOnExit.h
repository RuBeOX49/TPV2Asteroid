#pragma once
#include "../ecs/Component.h"
#include "../ecs/Entity.h"
#include "Transform.h"

class DisableOnExit : public Component {
private:
	Transform* bulletData;
public:
	static const int id = _DISABLEONEXIT;
	DisableOnExit() {};
	virtual void initComponent();
	virtual void update();
};