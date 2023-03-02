#include "DeAcceleration.h"
#include "../ecs/Entity.h"
#include "Transform.h"
#include "../game/Game.h"


void DeAcceleration::initComponent() {
	transform = ent->getComponent<Transform>();
}


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
