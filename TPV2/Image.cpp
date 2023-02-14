#include "Image.h"

void Image::initComponent() {
	transform = gameObject->addComponent<Transfrom>();;
}

void Image::render() {
	texture->render(transform->getRect());
}