#pragma once
#include "GameState.h"
#include "CollisionsManager.h"
#include "AsteroidsManager.h"
class BattleState : public GameState
{
public:

	BattleState();
	~BattleState();

private:

	CollisonsManager* collMngr;
	AsteroidsManager* astMngr;

	virtual void update();

	virtual void handleInput();
};
