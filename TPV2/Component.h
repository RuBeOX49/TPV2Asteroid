#pragma once
class GameObject;
class Component
{

public:
	Component();
	~Component();

	virtual void render(GameObject* g);
	virtual void update(GameObject* g);
	virtual void handleEvents(GameObject* g);
};

