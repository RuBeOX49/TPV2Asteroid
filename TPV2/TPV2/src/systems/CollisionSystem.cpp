#include "CollisionSystem.h"

void CollisionsSystem::receive(const Message& m)
{
	switch (m.id)
	{
	case _m_BATTLE_STATE_SETUP:
		onRoundStart();
		break;
	case _m_CHANGE_STATE:
		if(m.new_state_ID.state!=state_BATTLE)
		onRoundOver();
	default:
		break;
	}
}

void CollisionsSystem::initSystem()
{
	explosion= &sdlutils().soundEffects().at("BangSmall");
}

void CollisionsSystem::update()
{
	if (!active_)
		return;

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

void CollisionsSystem::onRoundOver()
{
	active_ = false;
}

void CollisionsSystem::onRoundStart()
{
	active_ = true;
}

void CollisionsSystem::handleFighterCollision(Entity* e, Entity* c)
{
	Transform* eTr = mngr_->getComponent<Transform>(e);
	Transform* cTr = mngr_->getComponent<Transform>(c);

	if (Collisions::collidesWithRotation(eTr->getPos(), eTr->getWidth(), eTr->getHeight(), eTr->getRotation(),
		cTr->getPos(), cTr->getWidth(), cTr->getHeight(), cTr->getRotation())) {
		explosion->play();
		
		auto hComponent = mngr_->getComponent<HealthComponent>(c);

		hComponent->damage(1);

		if (hComponent->getLives() == 0) {
			//astMngr->destroyAllAsteroids();
			Message m;
			m.id = _m_DESTROY_ALL_ASTEROIDS;
			Game::instance()->send(m);
			//GameStateMachine::instance()->changeState(new DeathState());
		}
		else {
			Message m;
			m.id = _m_DESTROY_ASTEROID;
			m.destroy_asteroid_data.e = e;
			Game::instance()->send(m);
			//GameStateMachine::instance()->pushState(new DamagedState());
		}
	}
}

void CollisionsSystem::handleBulletCollision(Entity* e, Entity* c)
{
	Transform* eTr = mngr_->getComponent<Transform>(e);
	Transform* cTr = mngr_->getComponent<Transform>(c);

	if (Collisions::collidesWithRotation(eTr->getPos(), eTr->getWidth(), eTr->getHeight(), eTr->getRotation(),
		cTr->getPos(), cTr->getWidth(), cTr->getHeight(), cTr->getRotation())) {
		//hay colisi�n, e desaparece
		Message m;
		m.id = _m_COLLISION_AST_BULLET;
		m.destroy_asteroid_data.e = e;
		m.destroy_bullet_data.b = c;
	}
}