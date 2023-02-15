#pragma once 

#include <SDL_events.h>
#include <vector>
#include <array>
#include "Component.h"	
class GameObject
{
	Manager* manager;
	std::vector<Component*> currentComponents;
	std::array<Component*, _LAST_CMP_ID> components;
	bool alive = true;


public:
	GameObject() : manager(nullptr) {};
	
	inline virtual ~GameObject() {};
	virtual void render();
	virtual void update();
	virtual void handleEvents();
	inline void setContext(Manager* mngr) {
		manager = mngr;
	}
	template<typename T, typename ...Ts>
	inline T* addComponent(Ts&& ...args) {
		T* c = new T(std::forward<Ts>(args)...);
		removeComponent<T>();
		currentComponents.push_back(c);
		components[T::id] = c;
		c->setContext(this, manager);
		c->initComponent();
		return c;
	}

	template<typename T>
	inline void removeComponent() {
		constexpr cmpId_type cId = T::id;

		if (components[cId] != nullptr) {
			auto iter = std::find(currentComponents.begin(),
				currentComponents.end(),
				components[cId]);
			currentComponents.erase(iter);
			delete components[cId];
			components[cId] = nullptr;
		}
	}

	template<typename T>
	inline bool hasComponent() {
		return components[T::id] != nullptr;
	}

};