#include "GameState.h"
#include "SDLApp.h"


//Manejo de eventos est�ndar
void GameState::handleEvents(SDL_Event event)
{
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT) {
			app->setExit(true);
		}
		for (auto var : sceneObjects)
		{
			var->handleEvents();
		}
	}
}

//Destructora
GameState::~GameState()
{
	for (auto var : sceneObjects)
	{
		delete var;
	}
}
//A sobreescribir mediante virtual void
void GameState::update()
{

}
//Render est�ndar
void GameState::render()
{
	for (auto var : sceneObjects)
	{
		var->render();
	}
}


