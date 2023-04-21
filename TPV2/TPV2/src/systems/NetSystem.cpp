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
			break;
		default:
			break;
		}
	}

}



bool NetSystem::host() {
	Uint16 puerto;

	cout << "Port Number: ";
	cin >> puerto;

	socket = SDLNet_UDP_Open(puerto);
	if (!socket) {
		cout << "Error en socket\n";
		return false;
	} 

	socketSet = SDLNet_AllocSocketSet(1);
	if (!socketSet) {
		cout << "Error en socketset\n";
		return false;
	} 

	SDLNet_UDP_AddSocket(socketSet, socket);
	packet = SDLNet_AllocPacket(MAX_SIZE);
	if (!packet) {
		cout << "Error en packet\n";
		return false;
	}

	port = SDLNetUtils::getSocketPort(socket);

	names.push_back(myName);
	hostName = myName;
	isHost = true;
	connected = false;


	return true;

}

bool NetSystem::client()
{

	Uint16 puerto;

	cout << "Server Port Number: ";
	cin >> puerto;

	std::string hostName;

	cout << "Server Host Name: ";
	cin >> hostName;

	socket = SDLNet_UDP_Open(puerto);
	if (!socket) {
		cout << "Error en socket\n";
		return false;
	}

	if (SDLNet_ResolveHost(&otherPlayerAdress, hostName.c_str(), puerto) < 0) {
		std::cout << "Could not resolve hostname";
		return false;
	}



	packet = SDLNet_AllocPacket(MAX_SIZE);
	if (!packet) {
		cout << "Error en packet\n";
		return false;
	}

	/*
	
	socket = SDLNet_UDP_Open(puerto);
	if (!socket) {
		cout << "Error en socket\n";
		return false;
	} 

	socketSet = SDLNet_AllocSocketSet(1);
	if (!socketSet) {
		cout << "Error en socketset\n";
		return false;
	} 

	SDLNet_UDP_AddSocket(socketSet, socket);
	packet = SDLNet_AllocPacket(MAX_SIZE);
	if (!packet) {
		cout << "Error en packet\n";
		return false;
	}

	*/




	return false;
}
