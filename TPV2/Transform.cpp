#include "Transform.h"

Transform::Transform()
{
	position = Vector2D(0, 0);
	velocity = Vector2D(0, 0);
	rotation = 0.0;
}

Transform::Transform(Vector2D position, Vector2D velocity, float rotation)
	: position(position), velocity(velocity), rotation(rotation) {

}

void Transform::lookAt(Vector2D point)
{
	Vector2D aux = position - point;
	rotation = aux.angle(velocity);
	velocity = velocity.rotate(rotation);
}

void Transform::rotate(float rotation)
{
	this->rotation += rotation;
	velocity = velocity.rotate(rotation);
}

void Transform::unrotate()
{
	velocity = velocity.rotate(-rotation);
	rotation = 0;
}

void Transform::move()
{
	position = position + velocity;
}

void Transform::update()
{
	move();
}
