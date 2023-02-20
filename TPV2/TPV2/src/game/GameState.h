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
    // Borra todos los Entity no vivos

    void addEntity(Entity* object);
    void refresh();
    //Inserta un nuevo Entity a la escena
    template<typename T = Entity, typename ...Ts>
    T* addEntity(Ts&& ...args) {
        T* e = new T();
        e->setAlive(true);
        e->setContext(this);
        e->initEntity(std::forward<Ts>(args)...);
        gObjs.push_back(e);
        return e;
    }
};
