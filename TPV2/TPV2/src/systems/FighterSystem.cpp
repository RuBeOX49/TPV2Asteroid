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
		break;
	case _m_CHANGE_STATE:
		if (m.new_state_ID.state != state_BATTLE)
			active_ = false;
		else active_ = true;
		break;
	case _m_COLLISION_AST_SHIP:
		onCollision_FighterAsteroid();
		break;
	default:
		break;
	}
}

void FighterSystem::update()
{
	if (!active_)
		return;
	fighterTransform->setPos(fighterTransform->getPos() + (fighterTransform->getVel() * Game::instance()->getDeltaTimeSeconds()));
	deAccData->setDeAccTimer(deAccData->getDeAaccTimer()+ Game::instance()->getDeltaTime());


	if (fighterTransform->getVel().magnitude() > 5 && deAccData->getDeAaccTimer() > 1000) {
		fighterTransform->setVel(fighterTransform->getVel() * 0.9);
		deAccData->setDeAccTimer(0);
	}
	else if (deAccData->getDeAaccTimer() > 1000) {
		fighterTransform->setVel(Vector2D(0, 0));
		deAccData->setDeAccTimer(0);
	}

		Vector2D pos = fighterTransform->getPos();

		if (pos.getX() < 0 - fighterTransform->getWidth()) {

			fighterTransform->setX(WIN_WIDTH);
		}
		else if (pos.getX() > WIN_WIDTH) {
			fighterTransform->setX(0 - fighterTransform->getWidth());
		}

		if (pos.getY() < 0 - fighterTransform->getHeight()) {
			fighterTransform->setY(WIN_HEIGHT);
		}
		else if (pos.getY() > WIN_HEIGHT) {
			fighterTransform->setY(0 - fighterTransform->getHeight());
		}
		
}

void FighterSystem::handleInput()
{
	if (!active_)
		return;

	Vector2D vel = Vector2D();
	if (InputHandler::instance()->isKeyDown(SDLK_a)) {
		fighterTransform->setRotation(fighterTransform->getRotation()-fighterCtrlData->getRotationFactor());
		fighterTransform->setVel(fighterTransform->getVel().rotate(-fighterCtrlData->getRotationFactor()));
	}
	else if (InputHandler::instance()->isKeyDown(SDLK_d)) {
		fighterTransform->setRotation(fighterTransform->getRotation() + fighterCtrlData->getRotationFactor());
		fighterTransform->setVel(fighterTransform->getVel().rotate(fighterCtrlData->getRotationFactor()));
	}
	if (InputHandler::instance()->isKeyDown(SDLK_w)) {
		fighterCtrlData->playThrust();
		vel = vel + Vector2D(0, -1);
		vel = vel.rotate(fighterTransform->getRotation()) * fighterCtrlData->getVel();
		if (vel.magnitude() != 0 && fighterTransform->getVel().magnitude() < 50)
			fighterTransform->setVel(vel + fighterTransform->getVel());
	}
	if (InputHandler::instance()->isKeyDown(SDLK_s)) {
		Message m;
		m.id = _m_SHOOT_BULLET;
		Game::instance()->send(m);
	}
	

}

void FighterSystem::onCollision_FighterAsteroid()
{
	Message m;
	m.id = _m_CHANGE_STATE;
	m.new_state_ID.state = state_DAMAGED;

}

void FighterSystem::onRoundOver()
{
	active_ = false;
	fighter->setAlive(false);
}

void FighterSystem::onRoundStart()
{
	active_ = true;
	for (auto var : mngr_->getEntities()) {
		if (var->getGroup() == _grp_FIGHTER)
			fighter = var;
	}
	fighterCtrlData = mngr_->getComponent<FighterCtrl>(fighter);
	fighterTransform = mngr_->getComponent<Transform>(fighter);
	deAccData = mngr_->getComponent<DeAcceleration>(fighter);
}
