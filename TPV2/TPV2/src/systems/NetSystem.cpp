#include "NetSystem.h"
#include "../sdlutils/SDLNetUtils.h"

void NetSystem::initSystem() {
	
	setup();

	Message m;

	m.id = _m_SETUP_MULTIPLAYER;
	m.isHost = isHost;
}

void NetSystem::update()
{
	NetMessage* m;
	if ((SDLNet_CheckSockets(socketSet, 0) > 0)&& SDLNet_SocketReady(socket)) {
		if (SDLNet_TCP_Recv(socket, &m, sizeof(m))>0) {
			switch (m->id) {
				case 
			}
		}
	}
}


void NetSystem::setup()
{
	std::cout << sizeof(NetMessage);

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
	Uint16 askedPort=100;

	if (SDLNet_ResolveHost(&ip, nullptr, askedPort) < 0) {
		SDLNetUtils::print_SDLNet_error();
		return false;
	}
	cout << "Puerto:" << ip.port<<endl;


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

	std::cout << "Como me llamo?";

	std::cin >> myName;

	names[0]=myName;
	hostName = myName;
	isHost = true,
	connected = false;

	NetMessage m;

	int resu = SDLNet_TCP_Recv(socket, &m, sizeof(m));




	for (int i = 0; i < m.nameSize; i++)
	{
		std::cout << m.name[i];
	}std::cout << "\n";
	names[1] = m.name;



	m.id = _m_REQUEST_ACCEPTED;

	auto nombreenc = myName.c_str();

	for (int i = 0; i < myName.size(); i++)
	{
		m.name[i] = nombreenc[i];
	}
	m.nameSize = myName.size();

	SDLNet_TCP_Send(socket, &m, sizeof(m));


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

	if (SDLNet_ResolveHost(&ip, askedHost.c_str(), askedPort) < 0) {
		SDLNetUtils::print_SDLNet_error();
		return false;
	}

	ip.port = askedPort;

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
	

	std::cout << "Como me llamo?";

	std::cin >> myName;

	names[1] = myName;

	NetMessage m;

	m.id = _m_CONNECTION_REQUEST;

	auto nombreenc = myName.c_str();

	for (int i = 0; i < myName.size(); i++)
	{
		m.name[i] = nombreenc[i];
	}
	m.nameSize = myName.size();

	SDLNet_TCP_Send(socket, &m, sizeof(m));

	

	int resu = SDLNet_TCP_Recv(socket, &m, sizeof(m));

	for (int i = 0; i < m.nameSize; i++)
	{
		std::cout << m.name[i];
	}std::cout << "\n";

	names[0] =m.name;

	
	return true;
}
