#include "FighterCtrl.h"
#include "../sdlutils/InputHandler.h"

void FighterCtrl::initComponent() {
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
