#pragma once
#include "GameObject.h"
#include "Texture.h"
#include "Vector2D.h"
#include <fstream>
#include <iostream>
#include <list>
class SDLApp;
class GameState
{
protected:
	std::list <GameObject*> sceneObjects;

	SDLApp* app;

public:

	GameState(SDLApp* game) : app(game) {};

	virtual ~GameState();

	virtual void update();

	virtual void render();

	virtual void handleEvents(SDL_Event event);

};

