//Server.h

#include "TCPServerSocket.cpp"
#include "SRI.cpp"

class Server{
	public:
	TCPServerSocket server;	
	map<int,SRI> SRIMap;
	
	Server(const char * _address, int _port, int _backlog);
	void Daemon();
};