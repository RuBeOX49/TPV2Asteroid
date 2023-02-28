#include "Gun.h"
#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/InputHandler.h"

Gun::Gun()
{
}

Gun::~Gun()
{
	
}

void Gun::handleEvents()
{
	if (InputHandler::instance()->isKeyDown(SDLK_s)) {
		if (sdlutils().currRealTime() - lastTimeShot <= 250)
		{
			//spawnea una bala nueva
			// shotSound->play(1);
		}
	}
}
