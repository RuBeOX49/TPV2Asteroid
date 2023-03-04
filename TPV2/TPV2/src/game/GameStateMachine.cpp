#include "GameStateMachine.h"

// Constructor
GameStateMachine::GameStateMachine() {}

// Destructor
GameStateMachine::~GameStateMachine() {
    clearStates();
    clearStatesToErase();
}

// Añade un estado nuevo
void GameStateMachine::pushState(GameState* newState) { gameStates.push(newState); }

// Borra el estado en el tope
void GameStateMachine::popState() {
    gameStatesToErase.push(gameStates.top());
    gameStates.pop();
}

// Erases todos los estados de la pila
void GameStateMachine::clearStates() {
    while (!gameStates.empty()) popState();
}

// Devuelve el estado del tope
GameState* GameStateMachine::currentState() { return gameStates.top(); }

// Cambia el estado actual
void GameStateMachine::changeState(GameState* newState) {
    clearStates();
    pushState(newState);
}

// Borra los estados de la pila de borrado
void GameStateMachine::clearStatesToErase() {
    while (!gameStatesToErase.empty()) {
        delete(gameStatesToErase.top());
        gameStatesToErase.pop();
    }
}