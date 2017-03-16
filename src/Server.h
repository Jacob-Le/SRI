//Server.h

#include "TCPServerSocket.cpp"
#include "SRI.cpp"

class Sever{
	public:
	TCPServerSocket server;	
	map<int,SRI> SRIMap;
	
	Sever(const char * _address, int _port, int _backlog);
	void Daemon();
};