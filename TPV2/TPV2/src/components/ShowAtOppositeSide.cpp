#include "ShowAtOppositeSide.h"

ShowAtOppositeSide::ShowAtOppositeSide(): transform(nullptr){}

void ShowAtOppositeSide::initComponent() {
	transform = ent->getComponent<Transform>();
}

void ShowAtOppositeSide::update() {
	Vector2D pos = transform->getPos();
	if (pos.getX() < 0) {
		pos.setX(WIN_WIDTH);
	}
	else if (pos.getX() > WIN_WIDTH) {
		pos.setX(0);
	}
	
	if (pos.getY() < 0) {
		pos.setY(WIN_HEIGHT);
	}
	else if (pos.getY() > WIN_HEIGHT) {
		pos.setY(0);
	}

}