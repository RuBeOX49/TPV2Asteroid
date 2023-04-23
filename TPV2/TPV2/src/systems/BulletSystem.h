#pragma once
#include "../ecs/System.h"
#include "../utils/Vector2D.h"
#include "../game/constants.h"
#include "../game/ecs_def.h"
#include "../components/Transform.h"
#include "../components/Gun.h"
#include "../game/Game.h"
#include "../components/FramedImage.h"

class BulletsSystem : public System {
public:
	// Reaccionar a los mensajes recibidos (llamando a m�todos correspondientes).
	void receive(const Message& m) override;
	// Inicializar el sistema, etc.
	void initSystem() override;
	// Si el juego est� parado no hacer nada, en otro caso mover las balas y
	// desactivar las que salen de la ventana como en la pr�ctica 1.
	void update() override;

	constexpr static sysId_type id = sys_BULLET;
private:
	// Para gestionar el mensaje de que el jugador ha disparado. A�adir una bala al
	// juego, como en la pr�ctica 1. Recuerda que la rotaci�n de la bala ser�a
	// vel.angle(Vector2D(0.0f,-1.0f))
	void shoot(Vector2D pos, Vector2D vel, double width, double height, grpId id);
	// Para gestionar el mensaje de que ha habido un choque entre una bala y un
	// asteroide. Desactivar la bala �b�.
	// Para gestionar el mensaje de que ha acabado la ronda. Desactivar todas las
	// balas, y desactivar el sistema.
	void onRoundOver();
	// Para gestionar el mensaje de que ha empezado una ronda. Activar el sistema.
	void onRoundStart();
	// Indica si el sistema est� activo o no (modificar el valor en onRoundOver y
	// onRoundStart, y en update no hacer nada si no est� activo)
	bool active_;
	bool multiplayer = false;

	// Busca la referencia al fighter en la escena
	void findFighter();

	// Actualiza las referencias y cambia el modo del sistema a multijugador
	void setupMultiplayer(bool isHost);

	SoundEffect* shotSound;
	Transform* shipTransform;
	Gun* shipGun;
	Transform* enemyShipTransform;
	Gun* enemyShipGun;
	
};