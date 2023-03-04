#include "Gun.h"
#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/InputHandler.h"
#include "../ecs/Entity.h"
#include "../game/Game.h"

#include "Image.h"
#include "DisableOnExit.h"




Gun::~Gun()
{
	
}

void Gun::initComponent() {
	shotSound = &sdlutils().soundEffects().at("GunShot");
	shipData = ent->getComponent<Transform>();
}

//Si se pulsa la s y hace m�s de 0,25s desde la �ltima se crea una nueva bala 
void Gun::handleInput()
{
	if (InputHandler::instance()->isKeyDown(SDLK_s)) {
		if (lastTimeShot > 250)
		{
			shotSound->play();
			Entity* bullet = mngr->addEntity();
			bullet->setGroup(_grp_BULLETS);
			
			bullet->addComponent<Transform>(
				//Posici�n
				shipData->getPos()+Vector2D(shipData->getWidth() / 2.0f, shipData->getHeight() / 2.0f)
				- Vector2D(0.0f, shipData->getHeight() / 2.0f + 5.0f + 12.0f).rotate(shipData->getRotation())
				- Vector2D(2.0f, 10.0f),
				//Velocidad
				Vector2D(0.0f, -1.0f).rotate(shipData->getRotation()) * (shipData->getVel().magnitude() + 5.0f)*bSpeed,
				//Ancho, alto y rotaci�n
				5, 20, shipData->getRotation());
			bullet->addComponent<Image>(Game::getTexture("Bullet"));
			bullet->addComponent<DisableOnExit>();
			lastTimeShot = 0;
		}
		
	}
	
}


//Incrementa el contador que controla el cooldown del disparo
void Gun::update() {
	lastTimeShot+=Game::instance()->getDeltaTime();
}