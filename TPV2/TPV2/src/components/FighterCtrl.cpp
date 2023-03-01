#include "FighterCtrl.h"
#include "../sdlutils/InputHandler.h"

FighterCtrl::FighterCtrl():transform(nullptr){}

void FighterCtrl::initComponent() {
	transform = ent->getComponent<Transform>();
}

void FighterCtrl::handleInput() {
	Vector2D vel=Vector2D();
	if (InputHandler::instance()->isKeyDown(SDLK_a)) {
		transform->rotate(-rotationFactor);
	}
	if (InputHandler::instance()->isKeyDown(SDLK_d)) {
		transform->rotate(rotationFactor);
	}
	if (InputHandler::instance()->isKeyDown(SDLK_w)) {
		vel = vel + Vector2D(0, -1);
	}
	if (InputHandler::instance()->isKeyDown(SDLK_s)) {
		vel = vel + Vector2D(0, 1);
	}
	//if(vel.getX()!=0||vel.getY()!=0)
	// vel = vel.normalize();
	vel = vel * shipSpeed;
	vel = vel.rotate(transform->getRotation());
	
	Vector2D newVel = transform->getVel() + vel;

	if(newVel.magnitude() > shipSpeed)
	{
		newVel = newVel.normalize() * shipSpeed;
	}

	transform->setVel(newVel);

}

void FighterCtrl::setVel(int newSpeed) {
	shipSpeed = newSpeed;
}