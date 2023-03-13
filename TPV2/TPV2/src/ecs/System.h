
#include "Message.h"

class Manager;
class System {

protected:

	Manager* mngr_;

public:

	virtual ~System() {

	}

	void setContext(Manager* mngr);

	virtual void initSystem() {}

	virtual void update() {}

	virtual void receive (const Message &msg) {}

};