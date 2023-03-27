#pragma once

#include <list>
#include "../ecs/Manager.h"

class SDLApp;
using namespace std;

class GameState {
protected:

    Manager* mngr;

public:
    // Constructor
    GameState();
    // Destructor
    virtual ~GameState();
    // Actualiza los objetos de la escea
    virtual void update();
    // Dibuja la escena en pantalla
    virtual void render() const;
    // Maneja el evento actual
    virtual void handleInput();
    // Devuelve el manager de la escena
    inline Manager* getManager() { return mngr; }
};
