#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include "GameStateMachine.h"

#define WIN_WIDTH 600
#define WIN_HEIGHT 800
#define FRAME_DELAY 32

class SDLApp
{
private:

	SDL_Renderer* renderer{ nullptr };
	SDL_Window* window{ nullptr };

	bool exit = false;

	GameStateMachine* states;

public:

	SDLApp();
	~SDLApp();
	void run();
	void render() const;
	void handleEvents();

	void setExit(bool toWhat);

	void changeState();
};

