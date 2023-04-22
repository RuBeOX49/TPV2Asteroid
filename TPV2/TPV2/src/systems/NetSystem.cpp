#include "NetSystem.h"
#include "../sdlutils/SDLNetUtils.h"

void NetSystem::initSystem() {
	
	setup();

}

void NetSystem::update()
{
	Message m;

	while (SDLNet_UDP_Recv(socket, packet) > 0)
	{
		m = (Message&)packet->data;

		switch (m.id)
		{
		case _m_CONNECTION_REQUEST:
			handleConnectionRequest(m);





		default:
			break;
		}


	}
}

void NetSystem::setup()
{
	bool resolved = false;
	while (!resolved) {
		char choice;
		cout << "Host or Client [H/C]: ";
		cin >> choice;

		switch (choice)
		{
		case 'H':
		case 'h':
			resolved=host();
			if (!resolved) cout << "error on host conexion";
			break;
		case 'C':
		case 'c':
			resolved = client();
			if (!resolved) cout << "error on client conexion";
			break;
		default:
			break;
		}
	}

}



bool NetSystem::host() {
	Uint16 askedPort;
	std::cout << "Enter a port number to use: ";
	cin >> askedPort;
	socket = SDLNet_UDP_Open(askedPort);
	if (!socket) {
		SDLNetUtils::print_SDLNet_error();
		return false;
	}

	socketSet = SDLNet_AllocSocketSet(1);
	if (!socketSet) {
		SDLNetUtils::print_SDLNet_error();
		return false;
	}

	SDLNet_UDP_AddSocket(socketSet, socket);
	packet = SDLNet_AllocPacket(512);
	if (!packet) {
		SDLNetUtils::print_SDLNet_error();
		return false;
	}

	port = SDLNetUtils::getSocketPort(socket);


	names.push_back(myName);
	hostName = myName;
	isHost = true,
	connected = false;
	return true;

}

bool NetSystem::client()
{

	Uint16 askedPort;
	std::string askedHost;

	std::cout << "Enter the host:" << endl;
	cin >> askedHost;
	std::cout << "Enter the port:"
		<< endl;
	cin >> askedPort;

	if (SDLNet_ResolveHost(&ip, askedHost.c_str(), port) < 0) {
		SDLNetUtils::print_SDLNet_error();
		return false;
	}

	isHost = false;

	socket = SDLNet_UDP_Open(port);
	if (!socket) {
		SDLNetUtils::print_SDLNet_error();
		return false;
	}

	socketSet = SDLNet_AllocSocketSet(1);
	if (!socketSet) {
		SDLNetUtils::print_SDLNet_error();
		return false;
	}

	SDLNet_UDP_AddSocket(socketSet, socket);
	packet = SDLNet_AllocPacket(512);
	if (!packet) {
		SDLNetUtils::print_SDLNet_error();
		return false;
	}

	port = SDLNetUtils::getSocketPort(socket);

	names.push_back(myName);

	Message m;

	m.id = _m_CONNECTION_REQUEST;
	m.side =isHost;
	auto i = 0u;


	for (; i < myName.size() && i < 10; i++) m.name[i] = myName[i];
	m.name[i] = 0;

	packet->address = ip;


	while (SDLNet_UDP_Send(socket, -1, packet) == 0) {
		std::cout << "Error enviando paquete\n";
	}



	if (SDLNet_CheckSockets(socketSet, 3000) > 0)
	{
		if (SDLNet_SocketReady(socket))
		{
			if (m.id == 12)
			{
				Message m;
				isHost = m.side;
				m.name[10] = 0;
				myName = m.name[0];
				connected = true;
			}
		}
	}

	if (!connected) {
		std::cout << "Could not connect to the other player " << std::endl;
		return false;
	}

	return true;
}

void NetSystem::handleConnectionRequest(Message m)
{
	if (!connected && isHost) {

		//hacer cosas de rellenar

		ip = packet->address;
		
		
		Message accepted;


		accepted.id = _m_REQUEST_ACCEPTED;


		packet->data = accepted;
		
		

		SDLNet_UDP_Send(socket, -1, packet);

		connected = true;
	}
}
