#pragma once
#ifndef GAMEOBJECT_H_
#define GAMEOBJECT_H_

#include <iostream>
#include <array>
#include <vector>
#include "../ecs/Component.h"
#include "Manager.h"
#include "../game/ecs_def.h"

using namespace std;

class Entity {
	friend class Manager;
protected:
	
	grpId_type group;
	bool alive;
	Manager* mngr;
	std::vector<Component*> currCmps;
	std::array<Component*, maxComponentId> cmps;
public:

	// Constructor
	Entity() : mngr(nullptr), cmps(), currCmps(), alive(true), group(_grp_NONE) {
		currCmps.reserve(maxComponentId);
	}
	// Destructor
	virtual ~Entity() { 
		for (Component* cmp : currCmps) {
			delete cmp;
			cmp = nullptr;
		}
		for (Component* cpm : cmps) {
			cpm = nullptr;
		}
	}

	//Devuelve el grupo de la Entity
	inline grpId_type getGroup() { return group; }
	//Asigna el grupo del GameObject
	inline void setGroup(grpId_type group) { this->group = group; }
	// Asigna el Manager del GameObject
	inline void setContext(Manager* _mngr) { mngr = _mngr; }
	// Inicializa el GameObject tras tener el contexto
	virtual void initEntity() {}
	// Devuelve si el GameObject est� vivo
	inline bool isAlive() { return alive; }
	// Asigna si el GameObject est� vivo o no
	inline void setAlive(bool _alive) { alive = _alive; }
	
	// Actualiza el GameObject
	virtual void update() {
		for (Component* cmp : currCmps) {
			cmp->update();
		}
	}
	// Dibuja el GameObject en pantalla
	virtual void render() const {
		for (Component* cmp : currCmps) {
			cmp->render();
		}
	}
	// Maneja los eventos del GameObject
	virtual void handleInput() {
		for (Component* cmp : currCmps) {
			cmp->handleInput();
		}
	}
};
#endif
