#pragma once
#include "../ecs/Manager.h"
#include "AsteroidsManager.h"
class CollisonsManager {

private:

	Manager* mngrRef;
	AsteroidsManager* astMngrRef;

public:

	CollisonsManager(Manager* mngrRef) : mngrRef(mngrRef) {}
	~CollisonsManager() {};

	void handlePhysics();






};