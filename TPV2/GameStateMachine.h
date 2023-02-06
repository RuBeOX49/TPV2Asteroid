#pragma once
#include <stack>
#include "GameState.h"
class GameStateMachine
{
private:

	std::stack<GameState*> states;
	std::stack<GameState*> garbage;

public:


	GameStateMachine() {};
	~GameStateMachine();
	GameState* currentState();

	void pushState(GameState* newState);

	void changeState(GameState* newState);

	void popState();

	void cleanGarbage();
};

