#include "Manager.h"
#include "Entity.h"
// Constructor
Manager::Manager() : entities() {
    entities.reserve(100);
}

// Destructor
Manager::~Manager() {
    for (Entity* gObj : entities) {
        delete(gObj);
        gObj = nullptr;
    }
}

// Actualiza los objetos de la escena
void Manager::update() {
    for (Entity* gObj : entities) {
        gObj->update();
    }

    refresh();
}

// Dibuja la escena en pantalla
void Manager::render() const {
    for (Entity* gObj : entities) {
        gObj->render();
    }
}

// Maneja el evento actual
void Manager::handleInput() {
    for (Entity* gObj : entities) {
        gObj->handleInput();
    }
}

// Borra todos los Entity no vivos
void Manager::refresh() {
    entities.erase(
        std::remove_if(entities.begin(), entities.end(), [](Entity* e) {
            if (e->isAlive()) {
                return false;
            }
            else {
                delete e;
                return true;
            }
            }), //
        entities.end());
}

void Manager::send(const Message& m)
{

}

void Manager::addEntity(Entity* object) {
    entities.push_back(object);
};

