#pragma once

#include "../game/ecs_def.h"
#include "Entity.h"
#include <list>
#include <vector>

using namespace std;
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

    vector<Entity*>& getEntities() { return entities; }

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

    template<typename T = Entity, typename ...Ts>
    inline T* addComponent(Entity* e, Ts&& ...args) {
        T* c = new T(std::forward<Ts>(args)...);
        constexpr cmpId_type cId = T::id;
        removeComponent<T>(c);
        e->currCmps.push_back();
        e->cmps[cId] = c;
        c->setContext(e, this);
        c->initComponent();
        return c;
    }

    template<typename T>
    inline void removeComponent(Entity* e) {
        constexpr cmpId_type cId = T::id;
        if (e->cmps[cId] != nullptr) {
            auto iter = std::find(e->currCmps.begin(),
                e->currCmps.end(),
                e->cmps[cId]);
            e->currCmps.erase(iter);
            delete e->cmps[cId];
            e->cmps[cId] = nullptr;
        }
    }
    template<typename T>
    inline bool hasComponent(Entity* e) {
        constexpr cmpId_type cId = T::id;
        return e->cmps[cId] != nullptr;
    }
    template<typename T>
    inline T* getComponent(Entity* e) {
        constexpr cmpId_type cId = T::id;
        return static_cast<T*>(e->cmps[cId]);
    }
    inline void setAlive(Entity* e, bool alive) {
        e->setAlive(alive);
    }
    inline bool isAlive(Entity* e) {
        return e->isAlive();
    }
    inline grpId_type groupId(Entity* e) {
        return e->getGroup();
    }

    
};

