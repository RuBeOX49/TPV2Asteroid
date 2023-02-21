#include "GameState.h"
#include "../game/Game.h"

// Constructor
GameState::GameState(){
    
}

// Destructor
GameState::~GameState() {
    delete mngr;
}

// Actualiza los objetos de la escena
void GameState::update() {
    mngr->update();

    mngr->refresh();
}

// Dibuja la escena en pantalla
void GameState::render() const {
    mngr->render();
}

// Maneja el evento actual
void GameState::handleInput() {
    mngr->handleInput();
}

