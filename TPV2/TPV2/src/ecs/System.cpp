#include "System.h"


void System::setContext(Manager* mngr)
{
	mngr_ = mngr;
}

void System::update() {
	mngr_->update();
}