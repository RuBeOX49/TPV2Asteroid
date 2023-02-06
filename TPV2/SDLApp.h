#pragma once
#include "SDL.h"
#include "SDL_image.h"

class SDLApp
{
private:
	SDL_Renderer* renderer{ nullptr };
	SDL_Window* window{ nullptr };

public:

	SDLApp();
	~SDLApp();
};

