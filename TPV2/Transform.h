#pragma once
#include "Component.h"
#include "src/utils/Vector2D.h"
#include "ecs.h"
#include <SDL.h>
class Transform : public Component {
private:

	Vector2D position;
	Vector2D velocity;

	int width, height;
	
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

	inline int getWidth() { return width; }
	inline void setWidth(int width) { this->width = width; }

	inline int getHeight() { return height; }
	inline void setHeight(int height) { this->height = height; }

	inline SDL_Rect getRect() {
		SDL_Rect rect;
		rect.x = position.getX();
		rect.y = position.getY();
		rect.w = width;
		rect.h = height;

		return rect;
	}

	inline float getRotation() { return rotation; }
	inline void setRotation(float newRotation) { rotation = newRotation; }

	void lookAt(Vector2D point);
	void rotate(float rotation);
	void unrotate();
	void move();
	virtual void update();

};

