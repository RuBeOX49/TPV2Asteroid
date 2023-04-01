#include "BulletSystem.h"

void BulletsSystem::receive(const Message& m)
{
	switch (m.id) {
	case _m_BATTLE_STATE_SETUP:
		onRoundStart();
		break;
	case _m_SHOOT_BULLET:
		shoot(
			//Pos
			shipTransform->getPos() + Vector2D(shipTransform->getWidth() / 2.0f, shipTransform->getHeight() / 2.0f)
			- Vector2D(0.0f, shipTransform->getHeight() / 2.0f + 5.0f + 12.0f).rotate(shipTransform->getRotation())
			- Vector2D(2.0f, 10.0f), 
			//Vel
			Vector2D(0.0f, -1.0f).rotate(shipTransform->getRotation()) * (shipTransform->getVel().magnitude() + 5.0f) * shipGun->getBulletSpeed(),
			//Width, Height
			5,20);
	default:
		break;
	}
}

void BulletsSystem::initSystem()
{
	shotSound = &sdlutils().soundEffects().at("GunShot");
	shotSound->setVolume(10);
}

void BulletsSystem::update()
{
	if (!active_)
		return;
	shipGun->setLastTimeShot(shipGun->getLastTimeShot() + Game::instance()->getDeltaTime());
	for (auto var : mngr_->getEntities()) {
		if (var->getGroup() == _grp_BULLETS) {
			Transform* bulletTransform = mngr_->getComponent<Transform>(var);
			bulletTransform->setPos(bulletTransform->getPos() + (bulletTransform->getVel() * Game::instance()->getDeltaTimeSeconds()));
			Vector2D currentPos = mngr_->getComponent<Transform>(var)->getPos();
			if (currentPos.getX() > WIN_WIDTH || currentPos.getY() > WIN_HEIGHT ||
				currentPos.getX() < 0 || currentPos.getY() < 0) {
				var->setAlive(false);
			}
		}
	}
}

void BulletsSystem::shoot(Vector2D pos, Vector2D vel, double width, double height)
{
	if (shipGun->getLastTimeShot() > 250)
	{
		shotSound->play();
		Entity* bullet = mngr_->addEntity();
		bullet->setGroup(_grp_BULLETS);

		mngr_->addComponent<Transform>(bullet,pos,
			//Velocidad
			vel,
			//Ancho, alto y rotacion
			width, height, shipTransform->getRotation());
		mngr_->addComponent<FramedImage>(bullet, Game::getTexture("Bullet"));
		
		shipGun->setLastTimeShot(0);
	}
}

void BulletsSystem::onRoundOver()
{
	active_ = false; 
}

void BulletsSystem::onRoundStart()
{

	active_ = true;
	for (auto var : mngr_->getEntities()) {
		if (var->getGroup() == _grp_FIGHTER) {
			shipTransform = mngr_->getComponent<Transform>(var);
			shipGun = mngr_->getComponent<Gun>(var);
		}
	}
	 
}
