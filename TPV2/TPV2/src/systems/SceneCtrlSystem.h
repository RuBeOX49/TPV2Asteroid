#pragma once
#include "../ecs/System.h"
#include "../utils/Vector2D.h"
#include "../game/constants.h"
#include "../game/ecs_def.h"



class SceneCtrlSystem : public System {
public:
	// Reaccionar a los mensajes recibidos (llamando a m�todos correspondientes).
	void receive(const Message& m) override;
	// Inicializar el sistema, etc.
	void initSystem() override;
	// Si el juego no est� parado y el jugador pulsa SDLK_SPACE cambia el estado
	// como en la pr�ctica 1, etc. Tiene que enviar mensajes correspondientes cuando
	// empieza una ronda o cuando empieza una nueva partida.
	void update() override;

	constexpr static sysId_type id = sys_SCENECTRL;
private:
	// Para gestionar el mensaje de que ha habido un choque entre el fighter y un
	// un asteroide. Tiene que avisar que ha acabado la ronda, quitar una vida
	// al fighter, y si no hay m�s vidas avisar que ha acabado el juego (y quien
	// es el ganador).
	void onCollision_FighterAsteroid(int remainingHealth);
	// Para gestionar el mensaje de que no hay m�s asteroides. Tiene que avisar que
	// ha acabado la ronda y adem�s que ha acabado el juego (y quien es el ganador)
	void onAsteroidsExtinction();
	stateID state_; // El estado actual del juego (en lugar del componente State)

	void setupMultiplayer(bool isHost);

	void initDefeatState();
	void initVictoryState();
	//NOTAS:
	//Como manejamos el cambio de escenas desde los mensajes, no necesitamos la variable winner_ para determinar la escena a la que cambiar
};