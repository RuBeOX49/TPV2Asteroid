#include "GameStateMachine.h"

//Destructructora, quitamos el último estado y limpiamos la basura restante
GameStateMachine::~GameStateMachine()
{
	while (!states.empty())
	{
		popState();
	}
	cleanGarbage();
}

//Devolvemos el estado que se encuentra en la cima de la pila o nullptr en caso contrario

GameState* GameStateMachine::currentState()
{
	if (states.empty())
	{
		return nullptr;
	}
	else return states.top();
}

//Introducimos un estado nuevo en la pila
void GameStateMachine::pushState(GameState* newState)
{
	states.push(newState);
}

//Cambiamos el estado si no es el mismo que ya hay en la pila
void GameStateMachine::changeState(GameState* newState)
{
	if (newState == currentState())
	{
		return;
	}
	popState();
	states.push(newState);
}

//Quitamos el estado que hay en la cima de la pila y añadimos su contenido al recolector de basura

void GameStateMachine::popState()
{
	if (states.empty()) {
		return;
	}
	auto pointer = states.top();
	garbage.push(pointer);
	states.pop();
}

//Limpiamos la basura que se encuentra marcada
void GameStateMachine::cleanGarbage()
{
	while (!garbage.empty())
	{
		delete(garbage.top());
		garbage.pop();
	}
}


