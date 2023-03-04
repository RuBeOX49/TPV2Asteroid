#pragma once
#include "Game.h"
#include "BattleState.h"
#include "PauseState.h"
#include "../sdlutils/SDLUtils.h"
// Constructora
Game::Game() {

	// Creacion de la ventana
	SDLUtils::init("quaso", WIN_WIDTH, WIN_HEIGHT, "src/game/game.resources.json");
	utils = SDLUtils::instance();
	window = utils->window();
	renderer = utils->renderer();
	//utils->toggleFullScreen();
	gameFont = new Font("resources/fonts/NES-Chimera.ttf", 20);

	// Maquina de estados
	gameStateMachine = GameStateMachine::instance();
	exit = false;
	gameStateMachine->pushState(new BattleState());
}

// Destructora
Game::~Game() {

	delete gameFont;

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

// Ejecuta el juego
void Game::run() {

	uint32_t startTime, frameTime;
	startTime = SDL_GetTicks();

	Uint64 NOW = SDL_GetPerformanceCounter();
	Uint64 LAST = 0;

	while (!exit) {
		InputHandler::instance()->refresh();
		frameTime = SDL_GetTicks() - startTime;
		update();

		LAST = NOW;
		NOW = SDL_GetPerformanceCounter();

		deltaTime = (double)((NOW - LAST) * 1000 / (double)SDL_GetPerformanceFrequency());

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

	if (InputHandler::instance()->closeWindowEvent()) {
		exit = true;
	}

	gameStateMachine->currentState()->handleInput();
}

// Devuelve la Texture pedida
Texture* Game::getTexture(TextureName texture) { return &SDLUtils::instance()->images().at(texture); }

Font* Game::getGameFont()
{
	return gameFont;
}

// Pausa el juego
void Game::pauseGame() { Game::instance()->gameStateMachine->pushState(new PauseState()); }

// Reanuda el juego
void Game::resumeGame() { Game::popGameState(); }

// Elimina el estado en la cima de la pila
void Game::popGameState() { Game::instance()->gameStateMachine->popState(); }

void Game::loseGame()
{
	Game::instance()->gameStateMachine->popState();
	// Game::instance()->gameStateMachine->pushState(new LoseState());
}

// Cierra el juego
void Game::quitGame() { Game::instance()->exit = true; }

void Game::setExit(bool toWhat)
{
	exit = toWhat;
}


