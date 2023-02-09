#include "GameObject.h"
#include <SDL_events.h>
//Métodos tipo virtual a sobreescribir
void GameObject::render()
{
	for (auto component : currentComponents)
		component->render(this);
}

void GameObject::update()
{
	for (auto component : currentComponents)
		component->update(this);
}

void GameObject::handleEvents()
{
	for (auto component : currentComponents)
		component->handleEvents(this);
}

inline void GameObject::addComponent(Component* newComponent)
{

}


