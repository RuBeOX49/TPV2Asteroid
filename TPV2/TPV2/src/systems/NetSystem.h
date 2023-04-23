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

	bool canReceive = false;

	string myName = "";
	string hostName = "";

	
	//Recoge los mensajes recibidos de la red y los convierte a mensajes internos para su tratamiento en los sistemas
	void update() override;
	//Realiza paso a paso la conexion entre cliente y host
	void setup();

	void receive(const Message& m) override;
	//Envia un mensaje de red por el canal TCP
	void sendNetMessage(msgId_type id);
	//Parte de setup() especifica para el host
	bool host();

	//Parte de setup() especifica para el cliente
	bool client();
	
	//Limpia los sockets y el socketSet para futuras conexiones
	void endConnection();
};