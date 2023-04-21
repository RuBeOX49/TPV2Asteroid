#include "NetSystem.h"
#include "network_messages.h"
#include "../sdlutils/SDLNetUtils.h"

void NetSystem::initSystem() {

}

bool NetSystem::initConnection(Uint16 port)
{
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

	return true;
}

bool NetSystem::initHost()
{
	Uint16 port;
	std::cout << "Enter a port number to use: ";
	if (!(std::cin >> port)) {
		std::cerr << "Invalid port" << std::endl;
		return false;
	}

	if (!initConnection(port))
		return false;

	names_[0] = myName;
	hostName = myName;
	host_ = true;
	side_ = 0;
	connected = false;
	return true;

}

bool NetSystem::initClient()
{
	Uint16 port;
	std::string host;

	std::cout << "Enter the host and port (separated by a space) of the host: "
		<< std::endl;
	if (!(std::cin >> host >> port)) {
		std::cerr << "Invalid host/port" << std::endl;
		return false;
	}

	if (SDLNet_ResolveHost(&otherPlayerAddress, host.c_str(), port) < 0) {
		SDLNetUtils::print_SDLNet_error();
		return false;
	}

	host_ = false;

	initConnection(0);

	names_[1] = myName;
	/*
	
	*/
	net::StartRequestMsg m;

	m.id = net::_CONNECTION_REQUEST;
	m.side = side_;
	string_to_chars(myName, m.name);

	packet->address = otherPlayerAddr_;
	SDLNetUtils::serializedSend(m, p_, socket);

	if (SDLNet_CheckSockets(socketSet, 3000) > 0)
	{
		if (SDLNet_SocketReady(socket))
		{
			SDLNetUtils::deserializedReceive(m, p_, socket);

			if (m.id == net::_REQUEST_ACCEPTED)
			{
				net::ReqAccMsg m;
				m.deserialize(p_->data);
				side_ = m.side;
				chars_to_string(names_[0], m.name);
				hostName = names_[0];
				host_ = false;
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

bool NetSystem::connect()
{

	char choice;
	bool done = false;
	bool success = false;

	std::cout << "What's your name? ";
	std::cin >> myName;
	std::cout << std::endl;
	std::cout << std::endl;


	while (!done) {
		std::cout << "Do you want to be host, client or exit [h/c/e]? "
			<< std::endl;
		std::cin >> choice;
		switch (choice) {
		case 'h':
		case 'H':
			success = initHost();
			done = true;
			break;
		case 'c':
		case 'C':
			success = initClient();
			done = true;
			break;
		case 'e':
		case 'E':
			done = true;
			break;
		default:
			break;
		}
	}

	return success;
}

void NetSystem::recieve(const Message& m)
{
	
}
