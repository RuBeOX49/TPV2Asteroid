#include "BulletSystem.h"

//Maneja los casos de cada mensaje
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
		break;
	case _m_COLLISION_AST_BULLET:
		mngr_->setAlive(m.destroy_bullet_data.b, false);
		break;
	case _m_BATTLE_RESTART:
		findFighter();
		break;
	case _m_SEND_FIGHTER:
		shipTransform = mngr_->getComponent<Transform>(m.fighter_address.f);
		shipGun = mngr_->getComponent<Gun>(m.fighter_address.f);
		break;
	case _m_SETUP_MULTIPLAYER:
		setupMultiplayer(m.isHost);
		break;
	default:
		break;
	}
}

//Obtiene el sonido del json y busca la referencia al fighter
void BulletsSystem::initSystem()
{
	shotSound = &sdlutils().soundEffects().at("GunShot");
	shotSound->setVolume(10);

	findFighter();

}

void BulletsSystem::findFighter() {
	for (auto var : mngr_->getEntities()) {
		if (mngr_->hasComponent<Gun>(var)) {
			shipTransform = mngr_->getComponent<Transform>(var);
			shipGun = mngr_->getComponent<Gun>(var);
		}
	}
}

void BulletsSystem::setupMultiplayer(bool isHost)
{
}

//Aumenta el cooldown y destruye la bala si esta fuera de la pantalla
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
				mngr_->setAlive(var, false);
			}
		}
	}
}

//Si se cumple el cooldown genera una bala en la posición de la nave y
//reinicia el cooldown
void BulletsSystem::shoot(Vector2D pos, Vector2D vel, double width, double height)
{
	if (shipGun->getLastTimeShot() > SHOOT_DELAY)
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

//Desactiva el sistema
void BulletsSystem::onRoundOver()
{
	active_ = false; 
}

//Activa el sistema
void BulletsSystem::onRoundStart()
{

	active_ = true;
	
	 
}
