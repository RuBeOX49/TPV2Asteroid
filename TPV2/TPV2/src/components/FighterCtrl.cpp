#include "FighterCtrl.h"
#include "../sdlutils/InputHandler.h"

FighterCtrl::FighterCtrl():transform(nullptr){}

void FighterCtrl::initComponent() {
	thrust = &sdlutils().soundEffects().at("Thrust");
	transform = ent->getComponent<Transform>();
}

//Rota e incrementa la velocdad de la nave a empujones
void FighterCtrl::handleInput() {
	Vector2D vel=Vector2D();
	if (InputHandler::instance()->isKeyDown(SDLK_a)) {
		transform->rotate(-rotationFactor);
	}
	if (InputHandler::instance()->isKeyDown(SDLK_d)) {
		transform->rotate(rotationFactor);
	}
	if (InputHandler::instance()->isKeyDown(SDLK_w)) {
		thrust->play();
		vel = vel + Vector2D(0, -1);
		vel = vel.rotate(transform->getRotation()) * shipSpeed;
		if (vel.magnitude() != 0&&transform->getVel().magnitude() < 50)
			transform->setVel(vel + transform->getVel());
	}

}

//Setter de velocidad
void FighterCtrl::setVel(int newSpeed) {
	shipSpeed = newSpeed;
}