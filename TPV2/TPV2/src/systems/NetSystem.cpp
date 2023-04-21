#include "NetSystem.h"
#include "network_messages.h"
#include "../sdlutils/SDLNetUtils.h"

void NetSystem::initSystem() {
	bool resolved=false;
	while (!resolved) {
		char choice;
		cout << "Host or Client [H/C]: ";
		cin >> choice;

		switch (choice)
		{
		case 'H':
		case 'h':
			resolved=host();
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

	return true;

}