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
	fighterTransform = mngr_->addComponent<Transform>(fighter, Vector2D(WIN_WIDTH / 2, WIN_HEIGHT / 2), Vector2D(), 40, 40, 0);
	mngr_->addComponent<HealthComponent>(fighter);
	deAccData = mngr_->addComponent<DeAcceleration>(fighter);
	mngr_->addComponent<Gun>(fighter);
	mngr_->addComponent<FramedImage>(fighter, Game::getTexture("Ship"));
	fighterCtrlData = mngr_->addComponent<FighterCtrl>(fighter);
	thrust = &sdlutils().soundEffects().at("Thrust");
	thrust->setVolume(10);

	Message m;

	m.id = _m_SEND_FIGHTER;
	m.fighter_address.f = fighter;

	Game::instance()->send(m);
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
		break;
	case _m_SETUP_MULTIPLAYER:
		onRoundStart();
		setupMultiplayer(m.name,m.nameRival, m.isHost);
		break;
	case _m_NET_OTHER_FIGHTER_FORWARD:
		enemyForward();
		break;
	case _m_NET_OTHER_FIGHTER_LEFT:
		enemyRotation(true);
		break;
	case _m_NET_OTHER_FIGHTER_RIGHT:
		enemyRotation(false);
		break;
	default:
		break;
	}
}

void FighterSystem::enemyForward() {
	Vector2D vel = Vector2D();
	thrust->play();
	vel = vel + Vector2D(0, -1);
	vel = vel.rotate(enemyFighterTransform->getRotation()) * fighterCtrlData->getVel();
	if (vel.magnitude() != 0 && enemyFighterTransform->getVel().magnitude() < 50)
		enemyFighterTransform->setVel(vel + enemyFighterTransform->getVel());
}

void FighterSystem::enemyRotation(bool left) {
	float rotation = left ? -fighterCtrlData->getRotationFactor() : fighterCtrlData->getRotationFactor();
	enemyFighterTransform->setRotation(enemyFighterTransform->getRotation() + rotation);
	enemyFighterTransform->setVel(enemyFighterTransform->getVel().rotate(rotation));
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
		if (multiplayer) {
			enemyFighterTransform->setPos(enemyFighterTransform->getPos() + (enemyFighterTransform->getVel() * Game::instance()->getDeltaTimeSeconds()));
			deAccData->setDeAccTimer(deAccData->getDeAaccTimer() + Game::instance()->getDeltaTime());


			if (enemyFighterTransform->getVel().magnitude() > 5 && deAccData->getDeAaccTimer() > 1000) {
				enemyFighterTransform->setVel(enemyFighterTransform->getVel() * 0.9);
				deAccData->setDeAccTimer(0);
			}
			else if (deAccData->getDeAaccTimer() > 1000) {
				enemyFighterTransform->setVel(Vector2D(0, 0));
				deAccData->setDeAccTimer(0);
			}

			Vector2D pos = enemyFighterTransform->getPos();

			if (pos.getX() < 0 - enemyFighterTransform->getWidth()) {

				enemyFighterTransform->setX(WIN_WIDTH);
			}
			else if (pos.getX() > WIN_WIDTH) {
				enemyFighterTransform->setX(0 - enemyFighterTransform->getWidth());
			}

			if (pos.getY() < 0 - enemyFighterTransform->getHeight()) {
				enemyFighterTransform->setY(WIN_HEIGHT);
			}
			else if (pos.getY() > WIN_HEIGHT) {
				enemyFighterTransform->setY(0 - enemyFighterTransform->getHeight());
			}
		}
}

//Comprueba la w para acelerar, a y d para girar y s para mandar el mensaje de disparo
void FighterSystem::handleInput()
{
	if (!active_)
		return;

	
	if (InputHandler::instance()->isKeyDown(SDLK_a)) {
		fighterTransform->setRotation(fighterTransform->getRotation()-fighterCtrlData->getRotationFactor());
		fighterTransform->setVel(fighterTransform->getVel().rotate(-fighterCtrlData->getRotationFactor()));

		if (multiplayer) {
			Message m;

			m.id = _m_SEND_NET_MESSAGE;

			m.netMessageID = _m_NET_OTHER_FIGHTER_LEFT;

			Game::instance()->send(m);
		}


	}
	else if (InputHandler::instance()->isKeyDown(SDLK_d)) {
		fighterTransform->setRotation(fighterTransform->getRotation() + fighterCtrlData->getRotationFactor());
		fighterTransform->setVel(fighterTransform->getVel().rotate(fighterCtrlData->getRotationFactor()));

		if (multiplayer) {
			Message m;

			m.id = _m_SEND_NET_MESSAGE;

			m.netMessageID = _m_NET_OTHER_FIGHTER_RIGHT;

			Game::instance()->send(m);
		}

	}
	if (InputHandler::instance()->isKeyDown(SDLK_w)) {
		Vector2D vel = Vector2D();
		thrust->play();
		vel = vel + Vector2D(0, -1);
		vel = vel.rotate(fighterTransform->getRotation()) * fighterCtrlData->getVel();
		if (vel.magnitude() != 0 && fighterTransform->getVel().magnitude() < 50)
			fighterTransform->setVel(vel + fighterTransform->getVel());

		if (multiplayer) {
			Message m;

			m.id = _m_SEND_NET_MESSAGE;

			m.netMessageID = _m_NET_OTHER_FIGHTER_FORWARD;

			Game::instance()->send(m);
		}

	}
	if (InputHandler::instance()->isKeyDown(SDLK_s)) {
		Message m;
		m.id = _m_SHOOT_BULLET;
		Game::instance()->send(m);

		if (multiplayer) {
			Message m;

			m.id = _m_SEND_NET_MESSAGE;

			m.netMessageID = _m_NET_OTHER_FIGHTER_SHOOTS;

			Game::instance()->send(m);
		}

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

void FighterSystem::setupMultiplayer(string name, string nameRival, bool isHost)
{

	//Generar Fighter Izquierdo (host)
	Vector2D playerFighterPos = isHost ? Vector2D(0, WIN_HEIGHT / 2) : Vector2D(WIN_WIDTH - 40, WIN_HEIGHT / 2);
	int rotation = isHost ? 90 : 270;

	

	fighter = mngr_->addEntity();
	fighter->setGroup(_grp_FIGHTER);
	fighterTransform = mngr_->addComponent<Transform>(fighter, playerFighterPos, Vector2D(), 40, 40, rotation);
	mngr_->addComponent<HealthComponent>(fighter);
	deAccData = mngr_->addComponent<DeAcceleration>(fighter);
	mngr_->addComponent<Gun>(fighter);
	mngr_->addComponent<FramedImage>(fighter, Game::getTexture("Ship"));
	fighterCtrlData = mngr_->addComponent<FighterCtrl>(fighter);
	thrust = &sdlutils().soundEffects().at("Thrust");
	thrust->setVolume(10);

	Texture* nameTexture = new Texture(SDLUtils::instance()->renderer(), name, *(Game::instance()->getGameFont()), build_sdlcolor("0x2020ffff"));
	auto text = mngr_->addEntity();
	nameTransform = mngr_->addComponent<Transform>(text, playerFighterPos + Vector2D(0, -fighterTransform->getHeight()/2), Vector2D(0, 0), nameTexture->width(), nameTexture->height());
	mngr_->addComponent<FramedImage>(text, nameTexture);

	//Generar Fighter Derecho (cliente)
	Vector2D enemyFighterPos = !isHost ? Vector2D(0, WIN_HEIGHT / 2) : Vector2D(WIN_WIDTH - 40, WIN_HEIGHT / 2);
	rotation = !isHost ? 90 : 270;

    enemyFighter = mngr_->addEntity();
	enemyFighter->setGroup(_grp_ENEMY_FIGHTER);
	enemyFighterTransform = mngr_->addComponent<Transform>(enemyFighter, enemyFighterPos, Vector2D(), 40, 40, rotation);
	mngr_->addComponent<HealthComponent>(enemyFighter);
	deAccData = mngr_->addComponent<DeAcceleration>(enemyFighter);
	mngr_->addComponent<Gun>(enemyFighter);
	mngr_->addComponent<FramedImage>(enemyFighter, Game::getTexture("Ship"));

	Texture* nameTextureRival = new Texture(SDLUtils::instance()->renderer(), nameRival, *(Game::instance()->getGameFont()), build_sdlcolor("0x2020ffff"));
	auto text1 = mngr_->addEntity();
	enemyNameTransform = mngr_->addComponent<Transform>(text, enemyFighterPos + Vector2D(0, -enemyFighterTransform->getWidth()), Vector2D(0, 0), nameTextureRival->width(), nameTextureRival->height());
	mngr_->addComponent<FramedImage>(text, nameTextureRival);

	Message m(_m_FIND_FIGHTER);
	Game::instance()->send(m);

	multiplayer = true;

}
