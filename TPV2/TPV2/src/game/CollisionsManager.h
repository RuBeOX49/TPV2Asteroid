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

	//N�cleo principal del motor de f�sicas, determina si hay alguna entidad colisionando, y resuelve las colisiones
	void handlePhysics();
	//Resoluci�n de la colisi�n Asteroide - Bala
	void handleBulletCollision( Entity* e, Entity* c);
	//Resoluci�n de la colisi�n Asteroide - Nave
	void handleFighterCollision(Entity* e, Entity* c);






};