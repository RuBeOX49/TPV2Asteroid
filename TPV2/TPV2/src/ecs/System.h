#pragma once
#include "../game/ecs_def.h"
#include "Manager.h"

class System {

protected:

	Manager* mngr_{ nullptr };

public:

	System() {}

	virtual ~System() {

	}

	void setContext(Manager* mngr);

	//Inicializa el sistema
	virtual void initSystem() {}
	//Separamos update, render y handleInput para mayor control. Usado principalmente en RenderSystem, BulletSystem y FighterSystem.
	virtual void update();

	virtual void render() const {}

	virtual void handleInput() {}

	virtual void receive (const Message &msg) {}

};