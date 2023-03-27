#ifndef GAME_STATE_MACHINE_H_
#define GAME_STATE_MACHINE_H_
#include <stack>
#include "GameState.h"
#include "../utils/Singleton.h"
using namespace std;

class GameStateMachine : public Singleton<GameStateMachine>{

    friend Singleton<GameStateMachine>;

private:
    stack<GameState*> gameStates;
    stack<GameState*> gameStatesToErase;
public:
    // Constructor
    GameStateMachine();
    // Destructor
    ~GameStateMachine();
    // Adds state
    void pushState(GameState* newState);
    // Erases state
    void popState();
    // Erases every state on the stack
    void clearStates();
    // Return current state
    GameState* currentState();
    // Changes the current state
    void changeState(GameState* newState);
    // Clears the game states to erase stack
    void clearStatesToErase();

    //Devuelve el Manager de la escena activa
    inline Manager* getCurrentManager() {
        return currentState()->getManager();
    }
};
#endif
