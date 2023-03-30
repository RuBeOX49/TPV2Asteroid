#include "DeAcceleration.h"
#include "../ecs/Entity.h"
#include "Transform.h"
#include "../game/Game.h"


void DeAcceleration::initComponent() {
	transform = mngr->getComponent<Transform>(ent);
}

//Cada segundo reduce la velocidad, y si la magnitud es menor que 5 detiene la nave
void DeAcceleration::update()
{	
	deAccTimer += Game::instance()->getDeltaTime();
	if (transform->getVel().magnitude() > 5&&deAccTimer>1000) {
		transform->setVel(transform->getVel() * 0.9);
		deAccTimer = 0;
	}
	else if(deAccTimer>1000){
		transform->setVel(Vector2D(0, 0));
		deAccTimer = 0;
	}
}
