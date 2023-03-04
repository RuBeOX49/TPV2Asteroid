#pragma once
#include "../sdlutils/SDLUtils.h"
class Entity;
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

	//Núcleo principal del motor de físicas, determina si hay alguna entidad colisionando, y resuelve las colisiones
	void handlePhysics();
	//Resolución de la colisión Asteroide - Bala
	void handleBulletCollision( Entity* e, Entity* c);
	//Resolución de la colisión Asteroide - Nave
	void handleFighterCollision(Entity* e, Entity* c);






};