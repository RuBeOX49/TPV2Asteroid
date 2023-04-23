#include "CollisionSystem.h"

//Maneja los mensajes
void CollisionsSystem::receive(const Message& m)
{
	switch (m.id)
	{
	case _m_BATTLE_STATE_SETUP:
		onRoundStart();
		multiplayer = false;
		break;
	case _m_CHANGE_STATE:
		if (m.new_state_ID.state != state_BATTLE)
			active_ = false;
		else active_ = true;
		break;
	case _m_SETUP_MULTIPLAYER:
		onRoundStart();
		setupMultiplayer(m.isHost);
		break;
	default:
		break;
	}
}

//Obtiene el sonido de explosion de fighter del json
void CollisionsSystem::initSystem()
{
	explosion= &sdlutils().soundEffects().at("BangSmall");
}


//Si está activo maneja las colisiones bala-asteroide
//y asteroide-fighter
void CollisionsSystem::update()
{
	if (!active_)
		return;

	if (multiplayer)
	{
		for (auto e : mngr_->getEntities()) {

			if (e->getGroup() == _grp_FIGHTER) {
				for (auto c : mngr_->getEntities()) {

					if (c->getGroup() == _grp_ENEMY_BULLETS)
					{
						handleNetCollision(e, c);
					}
				}
			}
		}
	}
	else {
		for (auto e : mngr_->getEntities())
		{
			if (e->getGroup() == _grp_ASTEROIDS) {
				for (auto c : mngr_->getEntities())
				{
					if (c->getGroup() == _grp_BULLETS)
					{
						handleBulletCollision(e, c);
					}

					if (c->getGroup() == _grp_FIGHTER)
					{

						handleFighterCollision(e, c);
					}
				}
			}
		}
	}
}

//Desactiva el sistema
void CollisionsSystem::onRoundOver()
{
	active_ = false;
}

//Activa el sistema
void CollisionsSystem::onRoundStart()
{
	active_ = true;
}

void CollisionsSystem::setupMultiplayer(bool isHost)
{
	isHost = isHost;
	multiplayer = true;
}

//Si hay colision fighter-asteroide, manda el mensaje con referencia al asteroide y quita una vida
void CollisionsSystem::handleFighterCollision(Entity* e, Entity* c)
{
	Transform* eTr = mngr_->getComponent<Transform>(e);
	Transform* cTr = mngr_->getComponent<Transform>(c);

	if (Collisions::collidesWithRotation(eTr->getPos(), eTr->getWidth(), eTr->getHeight(), eTr->getRotation(),
		cTr->getPos(), cTr->getWidth(), cTr->getHeight(), cTr->getRotation())) {
		explosion->play();
		
		auto hComponent = mngr_->getComponent<HealthComponent>(c);

		hComponent->damage(1);

		Message m;
		m.id = _m_COLLISION_AST_SHIP;
		m.destroy_asteroid_data.e = e;
		m.remainingHealth = hComponent->getLives();
		Game::instance()->send(m, true);
	}
}

//Si hay colision bala-asteroide se manda el mensaje con referencia a asteroide y bala 
void CollisionsSystem::handleBulletCollision(Entity* e, Entity* c)
{
	Transform* eTr = mngr_->getComponent<Transform>(e);
	Transform* cTr = mngr_->getComponent<Transform>(c);

	if (Collisions::collidesWithRotation(eTr->getPos(), eTr->getWidth(), eTr->getHeight(), eTr->getRotation(),
		cTr->getPos(), cTr->getWidth(), cTr->getHeight(), cTr->getRotation())) {
		
		Message m;
		m.id = _m_COLLISION_AST_BULLET;
		m.destroy_asteroid_data.e = e;
		m.destroy_bullet_data.b = c;

		Game::instance()->send(m);
	}
}

void CollisionsSystem::handleNetCollision(Entity* e, Entity* c) {
	Transform* eTr = mngr_->getComponent<Transform>(e);
	Transform* cTr = mngr_->getComponent<Transform>(c);

	if (Collisions::collidesWithRotation(eTr->getPos(), eTr->getWidth(), eTr->getHeight(), eTr->getRotation(),
		cTr->getPos(), cTr->getWidth(), cTr->getHeight(), cTr->getRotation())) {

		Message m2(_m_DEFEAT);

		Game::instance()->send(m2, true);

	}
}