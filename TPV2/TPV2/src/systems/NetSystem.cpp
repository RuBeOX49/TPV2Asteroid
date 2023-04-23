#include "NetSystem.h"
#include "../sdlutils/SDLNetUtils.h"
#include "../game/Game.h"

void NetSystem::initSystem() {
}

void NetSystem::update()
{
	if (!connected)
		return;

	NetMessage m;
	if ((SDLNet_CheckSockets(socketSet, 0) > 0)&& SDLNet_SocketReady(socket))
	{
		if (SDLNet_TCP_Recv(socket, &m, sizeof(m))>0) 
		{
			Message message;
			message.id = m.id;
			Game::instance()->send(message, true);
		}
		if (SDLNet_TCP_Recv(socket, &m, sizeof(m)) == 0)
		{
			//desconectado
			std::cout << "Desconectado";
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

	connected = true;

	Message m;

	m.id = _m_SETUP_MULTIPLAYER;
	m.isHost = isHost;
	m.name = isHost ? names[0]: names[1];
	m.enemyName = isHost? names[1]: names[0];
	Game::instance()->send(m, true);
}

void NetSystem::receive(const Message& m)
{
	switch (m.id)
	{
	case _m_SEND_NET_MESSAGE:
		sendNetMessage(m.netMessageID);
		break;
	case _m_DEFEAT:
		sendNetMessage(_m_NET_NOTIFIY_VICTORY);
		break;
	case m_DISCONNECT:
		endConnection();
		break;
	case _m_CHANGE_STATE:
		if (m.new_state_ID.state == state_MULTIPLAYER_DEFEAT
			|| m.new_state_ID.state == state_MULTIPLAYER_VICTORY
			|| m.new_state_ID.state == state_MULTIPLAYER_DISCONNECT)
			endConnection();
		break;
	default:
		break;
	}
}



void NetSystem::sendNetMessage(msgId_type id)
{
	NetMessage m;
	m.id = id;

	int sentData = SDLNet_TCP_Send(socket, &m, sizeof(m));
	if (sentData != sizeof(m))
	{
		//Error, desconectando
		Game::instance()->send(Message(m_DISCONNECT));
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


	string rivalName = "";

	for (int i = 0; i < m.nameSize; i++)
	{
		rivalName += m.name[i];
		std::cout << m.name[i];
	}std::cout << "\n";
	names[1] = rivalName;



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

	string rivalName="";
	for (int i = 0; i < m.nameSize; i++)
	{
		rivalName += m.name[i];
		std::cout << m.name[i];
	}std::cout << "\n";

	names[0] =rivalName;

	
	return true;
}

void NetSystem::endConnection()
{

	SDLNet_TCP_DelSocket(socketSet, socket);

	if (isHost)
		SDLNet_TCP_DelSocket(socketSet, masterSocket);

	connected = false;
}
