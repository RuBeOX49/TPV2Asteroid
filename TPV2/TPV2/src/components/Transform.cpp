#include "Transform.h"
#include "../game/Game.h"
#include <iostream>

//Constructora por defecto
Transform::Transform() : position_(Vector2D()), velocity_(Vector2D()), width_(0), height_(0), rotation_(0) {}

//Constructora normal
Transform::Transform(Vector2D pos, Vector2D vel, float w, float h, float r)
	: position_(pos), velocity_(vel), width_(w), height_(h), rotation_(r) {}

Transform::~Transform() {}


// Devuelve la distancia en valor absoluto desde un punto a otro
float Transform::getDistance(Vector2D other) {
	float x = other.getX() - position_.getX();
	float y = other.getY() - position_.getY();
	return abs(sqrt(x * x + y * y));
}

