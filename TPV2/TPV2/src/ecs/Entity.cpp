#include "Entity.h"
#include "../ecs/Component.h"

Entity::Entity(): mngr(nullptr), cmps(), currCmps(), alive(true), group(_grp_NONE) {
		currCmps.reserve(maxComponentId);
	}

Entity::~Entity()
{
	for (Component* cmp : currCmps) {
		delete cmp;
		cmp = nullptr;
	}
	for (Component* cpm : cmps) {
		cpm = nullptr;
	}
}

inline void Entity::setContext(Manager* _mngr)
{
	mngr = _mngr;
}

