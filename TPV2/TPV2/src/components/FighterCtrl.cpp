#include "FighterCtrl.h"
#include "../sdlutils/InputHandler.h"

FighterCtrl::FighterCtrl():transform(nullptr){}

void FighterCtrl::initComponent() {
	transform = ent->getComponent<Transform>();
}

void FighterCtrl::handleInput() {
	Vector2D vel;
	if (InputHandler::instance()->isKeyDown(SDLK_a)) {
		vel = vel + Vector2D(-1, 0);
	}
	if (InputHandler::instance()->isKeyDown(SDLK_d)) {
		vel = vel + Vector2D(1, 0);
	}
	if (InputHandler::instance()->isKeyDown(SDLK_w)) {
		vel = vel + Vector2D(0, -1);
	}
	if (InputHandler::instance()->isKeyDown(SDLK_s)) {
		vel = vel + Vector2D(0, 1);
	}

	vel = vel.normalize();
	vel = vel * shipSpeed;
	transform->setVel(vel);

}

void FighterCtrl::setVel(int newSpeed) {
	shipSpeed = newSpeed;
}