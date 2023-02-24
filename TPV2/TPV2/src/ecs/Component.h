#pragma once
#include <SDL.h>
#ifndef COMPONENT_H_
#define COMPONENT_H_
#include "../game/constants.h"
#include "../game/ecs_def.h"
#include "../game/GameState.h"

class Entity;
class Manager;

class Component {
protected:
	Entity* ent;
	Manager* mngr;
public:
	// Constructora
	Component() : ent(nullptr), mngr(nullptr) {}
	// Destructora
	virtual ~Component() {}
	// Asigna el GameObject y el Manager del Component
	inline void setContext(Entity* _ent, Manager* _mngr) {
		ent = _ent;
		mngr = _mngr;
	}
	// Inicializa el Component si es necesario
	virtual void initComponent() {}
	// Actualiza el Component
	virtual void update() {}
	// Dibuja el Component en pantalla
	virtual void render() const {}
	// Maneja los eventos del Component
	virtual void handleInput() {}
};

#endif // !COMPONENT_H_
