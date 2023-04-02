#pragma once
#include "../game/constants.h"
#include "../ecs/System.h"
#include "../sdlutils/Texture.h"

class RenderSystem : public System {
public:
	// Reaccionar a los mensajes recibidos (llamando a métodos correspondientes).
	void receive(const Message& m) override;
		// Inicializar el sistema, etc.
	void initSystem() override;
		// - Dibujar asteroides, balas y caza (sólo si el juego no está parado).
		// - Dibujar las vidas (siempre).
		// - Dibujar los mensajes correspondientes: si el juego está parado, etc (como en
		// la práctica 1)
		
	//Actualiza los frames a renderizar de todos los objetos en escena. Se hace independiente del update para poder hacer uso del reloj del sistema (deltaTime)
	void update() override;

	void render() const override;

	constexpr static sysId_type id = sys_RENDER;

private:
	// Para gestionar los mensajes correspondientes y actualizar los atributos
	// winner_ y state_.
	void onRoundStart();
	
	
	Texture* healthTexture;
	int currHealth = STARTING_HEALTH;
	

	uint winner_; // 0 - None, 1 - Asteroid, 2- Fighter
	uint state_; // El estado actual de juego (como en GameCtrlSystem)
};
