#include <SDL_net.h>
#include "../ecs/System.h"


class NetSystem : public System{
private:
	UDPsocket socket;
	UDPpacket* packet;
	SDLNet_SocketSet socketSet;
	Uint16 port;
public:
	void initSystem() override;
};