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
#include "../ecs/System.h"
#include <SDL_net.h>


using namespace std;
using TextureName = string;

class Game : public Singleton<Game> {

	friend Singleton<Game>;

private:
	SDLUtils* utils = nullptr;
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	GameStateMachine* gameStateMachine = nullptr;
	bool exit;
	double deltaTime = 0.0;

	std::array<System*, maxSystemId> _sys;

	std::vector<Message> msgs_;
	std::vector<Message> msgs_aux;
	
	
	Font* gameFont;

	// Constructora
	Game();

public:


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

	Font* getGameFont();

	template<typename T, typename ...Ts>
	static void newScene(Ts&& ...args) {
		T* scene = new T(std::forward<Ts>(args)...);
		Game::instance()->gameStateMachine->changeState(scene);
	}

	template<typename T, typename ...Ts>
	static void stackScene(Ts&& ...args) {
		T* scene = new T(std::forward<Ts>(args)...);
		Game::instance()->gameStateMachine->pushState(scene);
	}

	double getDeltaTime() { return deltaTime; }
	double getDeltaTimeSeconds() { return deltaTime / 1000.0; }

	// Pausa el juego
	void pauseGame();
	// Reanuda el juego
	void resumeGame();
	// Elimina el estado en la cima de la pila
	void popGameState();
	// Inicia el estado de derrota
	static void loseGame();
	// Cierra el juego
	static void quitGame();

	void setExit(bool toWhat);


	template<typename T, typename ...Ts>
	inline T* addSystem(Ts &&... args) {
		constexpr sysId_type sId = T::id;
		removeSystem<T>();
		System* s = new T(std::forward(args)...);
		s->setContext(gameStateMachine->getCurrentManager());
		s->initSystem();
		_sys[sId] = s;
		return static_cast<T*>(s);
	}

	template<typename T>
	inline T* getSystem() {
		constexpr sysId_type sId = T::id;
		return static_cast<T*>(_sys[sId]);
	}

	template<typename T>
	inline void removeSystem() {
		constexpr sysId_type sId = T::id;
		if (_sys[sId] != nullptr) {
			delete _sys[sId];
			_sys[sId] = nullptr;
		}
	}

	void setAllSystemsContext();

	void send(const Message& m, bool delay = false) {
		if (!delay) {
			for (System* s : _sys){
				if (s != nullptr)
					s->receive(m);
			}
		}
		else {
			msgs_.emplace_back(m);
		}
	}

	void flushMessages() {
		std::swap(msgs_, msgs_aux);
		for (auto& m : msgs_aux) {
			for (System* s : _sys) {
				if (s != nullptr)
					s->receive(m);
			}
		}
		msgs_aux.clear();
	}
};
#endif