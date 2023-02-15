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

SDLApp::~SDLApp()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();



	delete states;
}

void SDLApp::run()
{
	uint32_t starTime, frameTime;
	starTime = SDL_GetTicks();
	while (!exit) {
		
			SDL_RenderClear(renderer);
			handleEvents();
			frameTime = SDL_GetTicks() - starTime;
			if (frameTime >= FRAME_DELAY) {
				states->currentState()->update();
				states->cleanGarbage();
				starTime = SDL_GetTicks();
			}
			states->currentState()->render();
			SDL_RenderPresent(renderer);
		
	}
	states->cleanGarbage();
}

void SDLApp::render() const
{
	SDL_RenderClear(renderer);

	states->currentState()->render();

	SDL_RenderPresent(renderer);
}

void SDLApp::handleEvents()
{
	SDL_Event event = SDL_Event();
	states->currentState()->handleEvents(event);
}

void SDLApp::setExit(bool toWhat)
{
	exit = toWhat;
}

void SDLApp::changeState()
{
	//de verdad queremos volver a hacer esto?
}
