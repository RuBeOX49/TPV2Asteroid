#pragma once
#include "../ecs/Component.h"

class Generations : public Component {
private:


	int generation;



public:

	static const int id = _GENERATIONS;

	Generations(int generation): generation(generation) {}

	//Devuelve el número de generaciones
	inline int getGen() { return generation; }

	//Aumenta la generación
	inline void increaseGen() { generation++; }
};