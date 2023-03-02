#include "Gun.h"
#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/InputHandler.h"
#include "../ecs/Entity.h"
#include "../game/Game.h"

#include "Image.h"
#include "DisableOnExit.h"


Gun::Gun()
{
	
}

Gun::~Gun()
{
	
}

void Gun::initComponent() {
	shipData = ent->getComponent<Transform>();
}

void Gun::handleInput()
{
	if (InputHandler::instance()->isKeyDown(SDLK_s)) {
		if (lastTimeShot > 250)
		{
			// shotSound->play(1);
			Entity* bullet = mngr->addEntity();
			bullet->setGroup(_grp_BULLETS);
			//Position
			bullet->addComponent<Transform>(shipData->getPos()+Vector2D(shipData->getWidth() / 2.0f, shipData->getHeight() / 2.0f)
				- Vector2D(0.0f, shipData->getHeight() / 2.0f + 5.0f + 12.0f).rotate(shipData->getRotation())
				- Vector2D(2.0f, 10.0f),
				//Velocity
				Vector2D(0.0f, -1.0f).rotate(shipData->getRotation()) * (shipData->getVel().magnitude() + 5.0f),
				5, 20, shipData->getRotation());
			bullet->addComponent<Image>(Game::getTexture("Bullet"));
			bullet->addComponent<DisableOnExit>();
			lastTimeShot = 0;
		}
		
	}
	
}

void Gun::update() {
	lastTimeShot+=Game::instance()->getDeltaTime();
}