#include "NetSystem.h"
#include "../sdlutils/SDLNetUtils.h"

void NetSystem::initSystem() {
	
	setup();

}

void NetSystem::update()
{
	Message m;

	
}

void NetSystem::setup()
{
	std::cout << sizeof(Message);

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

	//masterSocket

	if (SDLNet_ResolveHost(&ip, nullptr, askedPort) < 0) {
		SDLNetUtils::print_SDLNet_error();
		return false;
	}

	masterSocket = SDLNet_TCP_Open(&ip);


	socketSet = SDLNet_AllocSocketSet(2);
	if (!socketSet) {
		SDLNetUtils::print_SDLNet_error();
		return false;
	}

	SDLNet_TCP_AddSocket(socketSet, masterSocket);

	std::cout << "Esperando a que se conecte el cliente\n";
	if (SDLNet_CheckSockets(socketSet, SDL_MAX_UINT32) > 0) {
		if (SDLNet_SocketReady(masterSocket)) {
			socket = SDLNet_TCP_Accept(masterSocket);
			cout << "SE CONECTO ALGUIEN" << endl;
			SDLNet_TCP_AddSocket(socketSet, socket);
			
		}
	}


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

	ip.port = port;
	isHost = false;

	//se conecta al masterSocket
	socket = SDLNet_TCP_Open(&ip);
	if (!socket) {
		SDLNetUtils::print_SDLNet_error();
		return false;
	}

	socketSet = SDLNet_AllocSocketSet(1);
	if (!socketSet) {
		SDLNetUtils::print_SDLNet_error();
		return false;
	}

	SDLNet_TCP_AddSocket(socketSet, socket);
	


	names.push_back(myName);


	Message m;

	int resu = SDLNet_TCP_Recv(socket, &m, sizeof(m));


	



	
	return true;
}

void NetSystem::handleConnectionRequest(Message m)
{
	
}
