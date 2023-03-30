#include "ShowAtOppositeSide.h"

ShowAtOppositeSide::ShowAtOppositeSide(): transform(nullptr){}

void ShowAtOppositeSide::initComponent() {
	transform = mngr->getComponent<Transform>(ent);
}


//Si la entidad sale del marco de la ventana, aparece al otro lado de la ventana
void ShowAtOppositeSide::update() {
	Vector2D pos = transform->getPos();

	if (pos.getX() < 0 - transform->getWidth()) {
		
		transform->setX(WIN_WIDTH);
	}
	else if (pos.getX() > WIN_WIDTH) {
		transform->setX(0 - transform->getWidth());
	}
	
	if (pos.getY() < 0 - transform->getHeight()) {
		transform->setY(WIN_HEIGHT);
	}
	else if (pos.getY() > WIN_HEIGHT) {
		transform->setY(0 - transform->getHeight());
	}

	

}