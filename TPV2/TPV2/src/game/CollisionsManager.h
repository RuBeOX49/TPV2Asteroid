#pragma once
#include "../sdlutils/SDLUtils.h"
class Manager;
class AsteroidsManager;
class CollisonsManager {

private:

	SoundEffect* explosion;
	Manager* mngr;
	AsteroidsManager* astMngr;

public:

	CollisonsManager(Manager* mngr, AsteroidsManager* astMngr) : mngr(mngr), astMngr(astMngr) {
		explosion = &sdlutils().soundEffects().at("BangSmall");
	}
	~CollisonsManager() {};

	void handlePhysics();






};