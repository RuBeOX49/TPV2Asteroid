#pragma once
#include "../ecs/Manager.h"
#include "../components/Follow.h"
#include "../components/Transform.h"
#include "../components/FramedImage.h"
#include "../components/ShowAtOppositeSide.h"
#include "../game/Game.h"

class AsteroidsManager
{
private:

	Manager* mngr;
	Entity* ship;
	int asteroidsAlive = 0;
	float timer = 0;

public:

	AsteroidsManager(Manager* mngr, Entity* ship) : mngr(mngr), ship(ship) {};
	~AsteroidsManager();


	void createAsteroid(int n);
	void addAsteroidFrequently();
	void destroyAllAsteroids();
	void onCollision(Entity* a);



};

