#pragma once
#ifndef SDLAPPLICATION_H_
#define SDLAPPLICATION_H_


#include <iostream>
#include <fstream>
#include <unordered_map>
#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/Texture.h"
#include "GameStateMachine.h"
#include "../sdlutils/InputHandler.h"
#include "constants.h"





using namespace std;
using TextureName = string;

class Game : public Singleton<Game> {
private:
	SDLUtils* utils = nullptr;
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	GameStateMachine* gameStateMachine = nullptr;
	bool exit;

public:
	// Constructora
	Game();
	// Destructora
	~Game();
	// Ejecuta el juego
	void run();
	// Ejecuta el juego
	void render() const;
	// Actualiza todas las entidades del juego
	void update();
	// Actualiza el juego en función al evento actual
	void handleInput();
	// Devuelve la Texture pedida
	static Texture* getTexture(TextureName texture);

	template<typename T, typename ...Ts>
	static void newScene(Ts&& ...args) {
		T* scene = new T(std::forward<Ts>(args)...);
		Game::instance()->gameStateMachine->changeState(scene);
	}

	// Pausa el juego
	static void pauseGame();
	// Reanuda el juego
	static void resumeGame();
	// Elimina el estado en la cima de la pila
	static void popGameState();
	// Cierra el juego
	static void quitGame();
};
#endif