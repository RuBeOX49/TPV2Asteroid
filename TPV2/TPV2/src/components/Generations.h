#pragma once
#include "../ecs/Component.h"

class Generations : public Component {
private:


	int generation;



public:

	static const int id = _GENERATIONS;

	Generations(int generation): generation(generation) {}

	//Devuelve el n�mero de generaciones
	inline int getGen() { return generation; }

	//Aumenta la generaci�n
	inline void increaseGen() { generation++; }
};