#pragma once
#include "../ecs/Component.h"
#include "Transform.h"

class Entity;
class Follow : public Component {
private:

	Transform* playerTransform;
	Transform* asteroidTransform;
	double followForce = 100.0;

public:

	static const int id = _FOLLOW;

	Follow(Transform* playerTransform) : playerTransform(playerTransform), asteroidTransform(nullptr) {}
	~Follow(){}

	virtual void initComponent();

	virtual void update();
};