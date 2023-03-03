#pragma once
#include "../ecs/Component.h"

class Generations : public Component {
private:


	int generation;



public:

	static const int id = _GENERATIONS;

	Generations(int generation): generation(generation) {}

	inline int getGen() { return generation; }

	inline void increaseGen() { generation++; }
};