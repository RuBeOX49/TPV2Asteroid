#pragma once
#include "Entity.h"
#include "../ecs/Component.h"
#include "Manager.h"

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

grpId_type Entity::getGroup()
{
	return group;
}

void Entity::setGroup(grpId_type group)
{
	this->group = group;
}

void Entity::setContext(Manager* _mngr)
{
	mngr = _mngr;
}

void Entity::initEntity()
{

}

bool Entity::isAlive()
{
	return alive;
}

void Entity::setAlive(bool _alive)
{
	alive = _alive;
}

