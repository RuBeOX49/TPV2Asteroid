#include <SDL_net.h>
#include "../ecs/System.h"
#include "../game/constants.h"
#include "../game/ecs_def.h"
#include <string>


class NetSystem : public System{
private:

	UDPsocket socket;
	UDPpacket* packet;
	SDLNet_SocketSet socketSet;
	UDPsocket masterSocket;
	Uint16 port;

	bool connected, isHost;
	vector<string> names;
	IPaddress ip;



public:
	constexpr static sysId_type id = sys_NET;

	string myName = "";
	string hostName = "";

	void initSystem() override;

	void update() override;

	void setup();

	void recieve(const Message& m);

	bool host();

	bool client();

	void handleConnectionRequest(Message m);
};