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
			5,20, _grp_BULLETS);
		break;
	case _m_COLLISION_AST_BULLET:
		mngr_->setAlive(m.destroy_bullet_data.b, false);
		break;
	case _m_BATTLE_RESTART:
	case _m_FIND_FIGHTER:
		findFighter();
		break;
	case _m_SEND_FIGHTER:
		shipTransform = mngr_->getComponent<Transform>(m.fighter_address.f);
		shipGun = mngr_->getComponent<Gun>(m.fighter_address.f);
		break;
	case _m_SETUP_MULTIPLAYER:
		onRoundStart();
		setupMultiplayer();
		break;
	case _m_NET_OTHER_FIGHTER_SHOOTS:
		shoot(
			//Pos
			enemyShipTransform->getPos() + Vector2D(enemyShipTransform->getWidth() / 2.0f, enemyShipTransform->getHeight() / 2.0f)
			- Vector2D(0.0f, enemyShipTransform->getHeight() / 2.0f + 5.0f + 12.0f).rotate(enemyShipTransform->getRotation())
			- Vector2D(2.0f, 10.0f),
			//Vel
			Vector2D(0.0f, -1.0f).rotate(enemyShipTransform->getRotation()) * (enemyShipTransform->getVel().magnitude() + 5.0f) * enemyShipGun->getBulletSpeed(),
			//Width, Height
			5, 20,
			//Group
			_grp_ENEMY_BULLETS);
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
		if (mngr_->hasComponent<Gun>(var) && mngr_->groupId(var) == _grp_FIGHTER) {
			shipTransform = mngr_->getComponent<Transform>(var);
			shipGun = mngr_->getComponent<Gun>(var);
		}
		if (mngr_->hasComponent<Gun>(var) && mngr_->groupId(var) == _grp_ENEMY_FIGHTER) {
			enemyShipTransform = mngr_->getComponent<Transform>(var);
			enemyShipGun = mngr_->getComponent<Gun>(var);
		}
	}
}

void BulletsSystem::setupMultiplayer()
{
	findFighter();
	multiplayer = true;
}

//Aumenta el cooldown y destruye la bala si esta fuera de la pantalla
void BulletsSystem::update()
{
	if (!active_)
		return;
	
	shipGun->setLastTimeShot(shipGun->getLastTimeShot() + Game::instance()->getDeltaTime());
	if (multiplayer)
		enemyShipGun->setLastTimeShot(enemyShipGun->getLastTimeShot() + Game::instance()->getDeltaTime());
	for (auto var : mngr_->getEntities()) {
		if (var->getGroup() == _grp_BULLETS||var->getGroup()==_grp_ENEMY_BULLETS) {
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
void BulletsSystem::shoot(Vector2D pos, Vector2D vel, double width, double height, grpId id)
{
	if (enemyShipGun == nullptr)
		findFighter();
	Gun* currentGun = (id == _grp_BULLETS) ? shipGun : enemyShipGun;
	if (currentGun->getLastTimeShot() > SHOOT_DELAY)
	{
		shotSound->play();
		Entity* bullet = mngr_->addEntity();
		bullet->setGroup(id);

		mngr_->addComponent<Transform>(bullet,pos,
			//Velocidad
			vel,
			//Ancho, alto y rotacion
			width, height, ((id == _grp_BULLETS) ? shipTransform : enemyShipTransform)->getRotation());
		mngr_->addComponent<FramedImage>(bullet, Game::getTexture("Bullet"));
		
		currentGun->setLastTimeShot(0);
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
