#pragma once
#include "Game.h"
#include "BattleState.h"

// Constructora
Game::Game() {

	// Creacion de la ventana
	SDLUtils::init("quaso", WIN_WIDTH, WIN_HEIGHT, "src/game/game.resources.json");
	utils = SDLUtils::instance();
	window = utils->window();
	renderer = utils->renderer();
	//utils->toggleFullScreen();


	// Maquina de estados
	gameStateMachine = new GameStateMachine();
	exit = false;
	gameStateMachine->pushState(new BattleState());
}

// Destructora
Game::~Game() {
	delete(gameStateMachine);

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

// Ejecuta el juego
void Game::run() {

	uint32_t startTime, frameTime;
	startTime = SDL_GetTicks();

	while (!exit) {
		InputHandler::instance()->refresh();
		frameTime = SDL_GetTicks() - startTime;
		update();
		if (frameTime >= DELAY_TIME) {
			startTime = SDL_GetTicks();
			render();
		}
		handleInput();
	}
	gameStateMachine->clearStates();
}

// Dibuja el juego en pantalla
void Game::render() const {
	SDL_RenderClear(renderer);
	gameStateMachine->currentState()->render();
	SDL_RenderPresent(renderer);
}

// Actualiza todas las entidades del juego
void Game::update() {
	gameStateMachine->currentState()->update();
	gameStateMachine->clearStatesToErase();
}

// Actualiza el juego en función al evento actual
void Game::handleInput() {
	gameStateMachine->currentState()->handleInput();
}

// Devuelve la Texture pedida
Texture* Game::getTexture(TextureName texture) { return &SDLUtils::instance()->images().at(texture); }

// Pausa el juego
void Game::pauseGame() { /*_game->gameStateMachine->pushState(new PauseMenuState(_game));*/ }

// Reanuda el juego
void Game::resumeGame() { Game::popGameState(); }

// Elimina el estado en la cima de la pila
void Game::popGameState() { Game::instance()->gameStateMachine->popState(); }

// Cierra el juego
void Game::quitGame() { Game::instance()->exit = true; }