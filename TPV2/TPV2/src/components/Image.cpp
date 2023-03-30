#include "Image.h"
#include "../ecs/Entity.h"
#include "../game/GameState.h"

// Constructor
Image::Image(Texture* _texture) : texture(_texture), transform(nullptr), flip(SDL_FLIP_NONE) {}

// Inicializa el componente y asigna su puntero a transform
void Image::initComponent() {
	transform = mngr->getComponent<Transform>(ent);
	
}

// Dibuja en pantalla la textura en el rectángulo del transform
void Image::render() const {
	texture->render(getRect(), transform->getRotation());
}

//Devuelve el rect dependiendo de la cámara
SDL_Rect Image::getRect() const {
	SDL_Rect rect = transform->getRect();

	return rect;
}

// Flipea la imagen horizontalmente
void Image::flipHorizontal() {
	flip = SDL_FLIP_HORIZONTAL;
}

// Flipea la imagen verticalmente
void Image::flipVertical() {
	flip = SDL_FLIP_VERTICAL;
}

void Image::flipNone() {
	flip = SDL_FLIP_NONE;
}