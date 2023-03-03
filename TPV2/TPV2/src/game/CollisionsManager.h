#pragma once
class Manager;
class AsteroidsManager;
class CollisonsManager {

private:

	Manager* mngr;
	AsteroidsManager* astMngr;

public:

	CollisonsManager(Manager* mngr, AsteroidsManager* astMngr) : mngr(mngr), astMngr(astMngr) {}
	~CollisonsManager() {};

	void handlePhysics();






};