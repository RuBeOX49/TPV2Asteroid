#include "FighterSystem.h"

void FighterSystem::receive(const Message& m)
{
}

void FighterSystem::initSystem()
{
}

void FighterSystem::update()
{
	if (!active_)
		return;
}

void FighterSystem::handleInput()
{


	/*Vector2D vel = Vector2D();
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
		if (vel.magnitude() != 0 && transform->getVel().magnitude() < 50)
			transform->setVel(vel + transform->getVel());
	}*/

}

void FighterSystem::onCollision_FighterAsteroid()
{
}

void FighterSystem::onRoundOver()
{
}

void FighterSystem::onRoundStart()
{
}
