#include "FighterSystem.h"


void FighterSystem::initSystem()
{

}

void FighterSystem::receive(const Message& m)
{
	switch (m.id)
	{
	case _m_BATTLE_STATE_SETUP:
		onRoundStart();
		active_ = true;

	default:
		break;
	}
}

void FighterSystem::update()
{
	if (!active_)
		return;
	fighterTransform->setPos(fighterTransform->getPos() + (fighterTransform->getVel() * Game::instance()->getDeltaTimeSeconds()));
}

void FighterSystem::handleInput()
{


	Vector2D vel = Vector2D();
	if (InputHandler::instance()->isKeyDown(SDLK_a)) {
		fighterTransform->setRotation(fighterTransform->getRotation()-fighterCtrlData->getRotationFactor());
		fighterTransform->setVel(fighterTransform->getVel().rotate(fighterTransform->getRotation()));
	}
	if (InputHandler::instance()->isKeyDown(SDLK_d)) {
		fighterTransform->setRotation(fighterTransform->getRotation() + fighterCtrlData->getRotationFactor());
		fighterTransform->setVel(fighterTransform->getVel().rotate(fighterTransform->getRotation()));
	}
	if (InputHandler::instance()->isKeyDown(SDLK_w)) {
		fighterCtrlData->playThrust();
		vel = vel + Vector2D(0, -1);
		vel = vel.rotate(fighterTransform->getRotation()) * fighterCtrlData->getVel();
		if (vel.magnitude() != 0 && fighterTransform->getVel().magnitude() < 50)
			fighterTransform->setVel(vel + fighterTransform->getVel());
	}

}

void FighterSystem::onCollision_FighterAsteroid()
{
}

void FighterSystem::onRoundOver()
{}

void FighterSystem::onRoundStart()
{
	for (auto var : mngr_->getEntities()) {
		if (var->getGroup() == _grp_FIGHTER)
			fighter = var;
	}
	fighterCtrlData = mngr_->getComponent<FighterCtrl>(fighter);
	fighterTransform = mngr_->getComponent<Transform>(fighter);

}
