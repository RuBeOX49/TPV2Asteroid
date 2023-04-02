#include "FighterSystem.h"

//Crea la nave
void FighterSystem::initSystem()
{
	//La Nave
	spawnFighter();
}

//Metodo que crea la nave
void FighterSystem::spawnFighter()
{
	Entity* fighter = mngr_->addEntity();
	fighter->setGroup(_grp_FIGHTER);
	fighterTransform = mngr_->addComponent<Transform>(fighter, Vector2D(WIN_WIDTH / 2, WIN_HEIGHT / 2), Vector2D(), 100, 100, 0);
	mngr_->addComponent<HealthComponent>(fighter);
	deAccData = mngr_->addComponent<DeAcceleration>(fighter);
	mngr_->addComponent<Gun>(fighter);
	mngr_->addComponent<FramedImage>(fighter, Game::getTexture("Ship"));
	fighterCtrlData = mngr_->addComponent<FighterCtrl>(fighter);
	thrust = &sdlutils().soundEffects().at("Thrust");
	thrust->setVolume(10);
}

//Maneja los mensajes recibidos
void FighterSystem::receive(const Message& m)
{
	switch (m.id)
	{
	case _m_BATTLE_STATE_SETUP:
		onRoundStart();
		break;
	case _m_CHANGE_STATE:
		if (m.new_state_ID.state != state_BATTLE)
			onRoundOver();
		else onRoundStart();
		break;
	case _m_COLLISION_AST_SHIP:
		onCollision_FighterAsteroid();
		break;
	case _m_BATTLE_RESTART:
		spawnFighter();
	default:
		break;
	}
}

//Si esta activo actualiza la posicion de la nave, bloquea su aceleracion a un maximo
//y a un minimo y comprueba si ha salido de pantalla para moverla al lado contrario
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

//Comprueba la w para acelerar, a y d para girar y s para mandar el mensaje de disparo
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
		thrust->play();
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

//Si se produce una colision resetea posicion, roticion y velocidad
void FighterSystem::onCollision_FighterAsteroid()
{
	fighterTransform->setPos(Vector2D(WIN_WIDTH/2,WIN_HEIGHT/2));
	fighterTransform->setRotation(0);
	fighterTransform->setVel(Vector2D());
}

//Desactiva el sistema
void FighterSystem::onRoundOver()
{
	active_ = false;
}

//Activa el sistema
void FighterSystem::onRoundStart()
{
	active_ = true;
	
}
