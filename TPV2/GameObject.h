#pragma once 
#include <SDL_events.h>
#include <vector>
#include <array>
#include "src/utils/Vector2D.h"
#include "Component.h"	
#include "ecs.h"
class GameObject
{
	std::vector<Component*> currentComponents;
	std::array<Component*, maxComponentID> components;
	bool alive = true;


public:

	inline virtual ~GameObject() {};
	inline virtual void render();
	inline virtual void update();
	inline virtual void handleEvents();
	inline virtual void addComponent(Component* newComponent);
};
