#include <SDL_net.h>
#include "../ecs/System.h"
#include "../game/constants.h"


class NetSystem : public System{
private:

	UDPsocket socket;
	UDPpacket* packet;
	SDLNet_SocketSet socketSet;
	Uint16 port;

	bool connected;
	IPaddress otherPlayerAdress;



public:
	constexpr static sysId_type id = sys_FIGHTER;

	string myName = "";
	string hostName = "";

	void initSystem() override;

	bool connect();

	void recieve(const Message& m);

	bool host();
};