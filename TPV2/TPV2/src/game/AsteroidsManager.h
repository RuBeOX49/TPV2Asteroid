#pragma once
#include "../ecs/Manager.h"

class AsteroidsManager
{
private:

	Manager* mngr;
	int asteroidsAlive = 0;

public:

	AsteroidsManager(Manager* mngr);
	~AsteroidsManager();


	void createAsteroid(int n);
	void addAsteroidFrequently();
	void destroyAllAsteroids();
	void onCollision(Entity* a);



};

