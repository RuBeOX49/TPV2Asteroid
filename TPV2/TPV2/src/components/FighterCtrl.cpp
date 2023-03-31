#include "FighterCtrl.h"
#include "../sdlutils/InputHandler.h"

FighterCtrl::FighterCtrl():transform(nullptr){}

void FighterCtrl::initComponent() {
	thrust = &sdlutils().soundEffects().at("Thrust");
}

//Setter de velocidad
void FighterCtrl::setVel(float newSpeed) {
	shipSpeed = newSpeed;
}

float FighterCtrl::getVel() {
	return shipSpeed;
}

float FighterCtrl::getRotationFactor() {
	return rotationFactor;
}

void FighterCtrl::playThrust() {
	thrust->play();
}