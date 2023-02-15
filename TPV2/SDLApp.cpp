#include "SDLApp.h"
#include <string>

SDLApp::SDLApp()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("Practica 2", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (window == nullptr || renderer == nullptr) throw std::string("Error loading SDL window or renderer");

	//cargado de texturas

	states = new GameStateMachine();

	


}
