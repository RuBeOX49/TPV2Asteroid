#pragma once
#include "../ecs/Component.h"
#include "../components/Transform.h"
#include "../ecs/Entity.h"

struct ShowAtOppositeSide : public Component
{

private:
	Transform* transform;

public:
	static const int id = _SHOWATOPPOSITESIDE;

	ShowAtOppositeSide();
	~ShowAtOppositeSide() {}

};

