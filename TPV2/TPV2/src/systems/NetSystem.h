#include <SDL_net.h>
#include "../ecs/System.h"


class NetSystem : public System{
private:

	bool host_;
	Uint8 side_; // 0 left 1 right


	UDPsocket socket;
	UDPpacket* packet;
	SDLNet_SocketSet socketSet;
	Uint16 port;

	bool connected;
	IPaddress otherPlayerAdress;


	bool initConnection(Uint16 port);

	bool initHost();
	bool initClient();

public:

	std::string myName = "waiting";
	std::string hostName = "waiting";
	std::array<std::string, 2> names_ = { "waiting", "waiting" };

	void initSystem() override;

	bool connect();

	void recieve(const Message& m);
};