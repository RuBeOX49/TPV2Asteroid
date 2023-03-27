#pragma once

#include "../game/ecs_def.h"
#include <list>
#include <vector>
#include <array>
#include "System.h"

using namespace std;
class Entity;
class Manager {
protected:

    vector<Entity*> entities;
   
   
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

    template<typename T, typename ...Ts>
    inline T* addSystem(Ts &&... args) {
        constexpr sysId_type sId = T::id;
        removeSystem<T>();
        System* s = new T(std::forward(args)...);
        s->setContext(this);
        s->initSystem();
        _sys[sId] = s;
        return static_cast<T*>(s);
    }

    template<typename T>
    inline T* getSystem() {
        constexpr sysId_type sId = T::id;
        return static_cast<T*>(_sys[sId]);
    }

    template<typename T>
    inline void removeSystem() {
        constexpr sysId_type sId = T::id;
        if( _sys[sId] != nullptr ) {
            delete _sys[sId];
            _sys[sId] = nullptr;
        }
    }

};

