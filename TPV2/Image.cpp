#include "Image.h"

void Image::initComponent() {
	transform = gameObject->addComponent<Transform>();;
}

void Image::render() {
	texture->render(transform->getRect());
}