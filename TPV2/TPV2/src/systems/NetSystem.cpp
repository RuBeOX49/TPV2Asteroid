#include "NetSystem.h"
#include "../sdlutils/SDLNetUtils.h"

void NetSystem::initSystem() {
	
	setup();

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

	m.id =11;
	m.side =isHost;
	auto i = 0u;
	for (; i < myName.size() && i < 10; i++) m.name[i] = myName[i];
	m.name[i] = 0;

	packet->address = ip;
	SDLNetUtils::serializedSend(m, packet, socket);

	if (SDLNet_CheckSockets(socketSet, 3000) > 0)
	{
		if (SDLNet_SocketReady(socket))
		{
			SDLNetUtils::deserializedReceive(m, packet, socket);

			if (m.id == _REQUEST_ACCEPTED)
			{
				net::ReqAccMsg m;
				m.deserialize(p_->data);
				side_ = m.side;
				chars_to_string(names_[0], m.name);
				hostName = names_[0];
				host_ = false;
				connected_ = true;
			}
		}
	}

	if (!connected_) {
		std::cout << "Could not connect to the other player " << std::endl;
		return false;
	}

	return true;
}