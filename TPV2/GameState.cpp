#include "GameState.h"
#include "SDLApp.h"


//Manejo de eventos estándar
void GameState::handleEvents(SDL_Event event)
{
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT) {
			app->setExit(true);
		}
		for each (auto var in sceneObjects)
		{
			var->handleEvents(event);
		}
	}
}

//Destructora
GameState::~GameState()
{
	for each (auto var in sceneObjects)
	{
		delete var;
	}
}
//A sobreescribir mediante virtual void
void GameState::update()
{

}
//Render estándar
void GameState::render()
{
	for each (auto var in sceneObjects)
	{
		var->render();
	}
}


