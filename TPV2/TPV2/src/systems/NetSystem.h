#include <SDL_net.h>
#include "../ecs/System.h"
#include "../game/constants.h"


class NetSystem : public System{
private:

	UDPsocket socket;
	UDPpacket* packet;
	SDLNet_SocketSet socketSet;
	Uint16 port;

	bool connected, isHost;
	vector<string> names;
	IPaddress otherPlayerAdress;



public:
	constexpr static sysId_type id = sys_NET;

	string myName = "";
	string hostName = "";

	void initSystem() override;

	void setup();


	void recieve(const Message& m);

	bool host();

	bool client();
};