#pragma once
#include "Message.h"

#include <list>
#include <vector>
#include "System.h"

using namespace std;
class Entity;
class Manager {
protected:

    vector<Entity*> entities;
    vector<System*> systems;
   
public:
    // Constructor
    Manager();
    // Destructor
    virtual ~Manager();
    // Actualiza los objetos de la escea
    virtual void update();
    // Dibuja la escena en pantalla
    virtual void render() const;
    // Maneja el evento actual
    virtual void handleInput();
    void addEntity(Entity* object);

    vector<Entity*> getEntities() { return entities; }

    // Borra todos los Entity no vivos
    void refresh();
    //Inserta un nuevo Entity a la escena
    template<typename T = Entity, typename ...Ts>
    T* addEntity(Ts&& ...args) {
        T* e = new T();
        e->setAlive(true);
        e->setContext(this);
        e->initEntity(std::forward<Ts>(args)...);
        entities.push_back(e);
        return e;
    }

    virtual void send(const Message& m);

};

