#pragma once
#include "../ecs/System.h"
#include "../components/Transform.h"
#include "../utils/Collisions.h"
#include "../sdlutils/SDLUtils.h"
#include "../components/Health.h"
#include "../game/Game.h"

class CollisionsSystem : public System {
public:
	// Reaccionar a los mensajes recibidos (llamando a métodos correspondientes).
	void receive(const Message& m) override;
		// Inicializar el sistema, etc.
	void initSystem() override;
		// Si el juego está parado no hacer nada, en otro caso comprobar colisiones como
		// en la práctica 1 y enviar mensajes correspondientes.
	void update() override;

	constexpr static sysId_type id = sys_COLLISION;

private:
	// Para gestionar el mensaje de que ha acabado una ronda. Desactivar el sistema.
	void onRoundOver();
		// Para gestionar el mensaje de que ha empezado una ronda. Activar el sistema.
		void onRoundStart();
		// Indica si el sistema está activo o no (modificar el valor en onRoundOver y
		// onRoundStart, y en update no hacer nada si no está activo)
		bool active_;
		bool multiplayer=false;
		bool isHost;
		SoundEffect* explosion;

		void setupMultiplayer(bool isHost);

		//Maneja las colisiones entre fighter y asteroide
		void handleFighterCollision(Entity* e, Entity* c);
		
		//Maneja las colisiones entre bala y asteroide
		void handleBulletCollision(Entity* e, Entity* c);

		//Maneja las colisiones entre bala enemiga y nave
		void handleNetCollision(Entity* e, Entity* c);
};