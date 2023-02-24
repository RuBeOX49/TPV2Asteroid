#pragma once
#ifndef COMPONENT_H_
#define COMPONENT_H_
#include <SDL.h>
#include "../game/constants.h"
#include "../game/ecs_def.h"

class Entity;
class Entity;

class Component {
protected:
	Entity* ent;
	Entity* gStt;
public:
	// Constructora
	Component() : ent(nullptr), gStt(nullptr) {}
	// Destructora
	virtual ~Component() {}
	// Asigna el GameObject y el Manager del Component
	inline void setContext(Entity* _ent, Entity* _gStt) {
		ent = _ent;
		gStt = _gStt;
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
