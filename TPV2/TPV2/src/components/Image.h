#pragma once
#ifndef IMAGE_H_
#define IMAGE_H_
#include "../ecs/Component.h"
#include "Transform.h"
#include "../sdlutils/Texture.h"

/*
	Se encarga de renderizar correctamente la imagen del objeto teniendo en cuenta
	si tiene una camara atachada
*/

class Image : public Component {
protected:
	Texture* texture;
	Transform* transform;
	SDL_RendererFlip flip;
public:
	static const int id = _IMAGE;
	// Constructora
	Image(Texture* _texture);
	// Inicializa el componente y asigna su puntero a transform
	virtual void initComponent();
	// Dibuja en pantalla la textura en el rect�ngulo del transform
	virtual void render() const;
	virtual SDL_Rect getRect() const;
	// Flipea la imagen horizontalmente
	void flipHorizontal();
	// Flipea la imagen verticalmente
	void flipVertical();
	// Desflipea la imagen
	void flipNone();
};
#endif // !IMAGE_H_
