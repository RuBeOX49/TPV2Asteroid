#pragma once
#ifndef GAMEOBJECT_H_
#define GAMEOBJECT_H_

#include <iostream>
#include <array>
#include <vector>

#include "../game/ecs_def.h"

class Component;
class Manager;

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
	Entity();
	// Destructor
	virtual ~Entity();

	//Devuelve el grupo de la Entity
	grpId_type getGroup();
	//Asigna el grupo del GameObject
	void setGroup(grpId_type group);
	// Asigna el Manager del GameObject
	void setContext(Manager* _mngr);
	// Inicializa el GameObject tras tener el contexto
	virtual void initEntity();
	// Devuelve si el GameObject está vivo
	bool isAlive();
	// Asigna si el GameObject está vivo o no
	void setAlive(bool _alive);
	
	//// Actualiza el GameObject
	//virtual void update() {
	//	for (Component* cmp : currCmps) {
	//		cmp->update();
	//	}
	//}
	//// Dibuja el GameObject en pantalla
	//virtual void render() const {
	//	for (Component* cmp : currCmps) {
	//		cmp->render();
	//	}
	//}
	//// Maneja los eventos del GameObject
	//virtual void handleInput() {
	//	for (Component* cmp : currCmps) {
	//		cmp->handleInput();
	//	}
	//}
};
#endif
