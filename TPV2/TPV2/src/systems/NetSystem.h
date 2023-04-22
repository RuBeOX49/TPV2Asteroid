#include <SDL_net.h>
#include "../ecs/System.h"
#include "../game/constants.h"
#include "../game/ecs_def.h"
#include <array>
#include <string>


class NetSystem : public System{
private:

	TCPsocket socket;
	SDLNet_SocketSet socketSet;
	TCPsocket masterSocket;
	Uint16 port;

	bool connected, isHost;
	string names[2];
	IPaddress ip;



public:
	constexpr static sysId_type id = sys_NET;

	string myName = "";
	string hostName = "";

	void initSystem() override;

	void update() override;

	void setup();

	void recieve(const Message& m);

	void sendNetMessage(msgId_type id);

	bool host();

	bool client();
};