#pragma once
#include "Component.h"
#include "src/utils/Vector2D.h"
#include "ecs.h"
class Transform : public Component {
private:

	Vector2D position;
	Vector2D velocity;

	float rotation;

public:

	static const int id = _TRANSFORM;
	Transform();
	Transform(Vector2D position, Vector2D velocity, float rotation = 0.0);
	virtual ~Transform(){};

	inline Vector2D& getPos() { return position; }
	inline void setPos(Vector2D newPos) { position = newPos; }

	inline Vector2D& getVel() { return velocity; }
	inline void setVel(Vector2D newVel) { velocity = newVel; }

	inline float getRotation() { return rotation; }
	inline void setRotation(float newRotation) { rotation = newRotation; }

	void lookAt(Vector2D point);
	void rotate(float rotation);
	void unrotate();
	void move();
	virtual void update();

};

